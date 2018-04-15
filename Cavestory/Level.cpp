#include "Level.h"
#include "Graphics.h"
#include "SDL.h"
#include <sstream>
#include "tinyxml2.h"
#include "easylogging++.h"

using namespace tinyxml2;

Level::Level()
{
}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics & graphics) :
	_mapName(mapName),
	_spawnPoint(spawnPoint),
	_mapSize(Vector2().zero())
{
	this->LoadMap(mapName, graphics);
}

Level::~Level()
{
}

void Level::Update(float elapsedTime)
{

}

void Level::Draw(Graphics & graphics)
{
	for (size_t i = 0; i < this->_tiles.size(); i++)
	{
		this->_tiles.at(i).Draw(graphics);
	}
}

void Level::LoadMap(std::string mapName, Graphics & graphics)
{
	std::string basePath = ".//content//maps//";
	std::string tilesetsPath = ".//content//tilesets//";
	std::stringstream mapFilePath;
	mapFilePath << basePath << mapName << ".tmx";

	tinyxml2::XMLDocument doc;
	doc.LoadFile(mapFilePath.str().c_str());

	XMLElement* pMapNode = doc.FirstChildElement("map");

	int mapWidth, mapHeight;
	pMapNode->QueryIntAttribute("width", &mapWidth);
	pMapNode->QueryIntAttribute("height", &mapHeight);

	this->_mapSize = Vector2(mapWidth, mapHeight);

	int tileWidth, tileHeight;
	pMapNode->QueryIntAttribute("tilewidth", &tileWidth);
	pMapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->_tileSize = Vector2(tileWidth, tileHeight);

	XMLElement* pTileset = pMapNode->FirstChildElement("tileset");

	while (pTileset) {
		int firstGid;
		pTileset->QueryIntAttribute("firstgid", &firstGid);

		const char* tilesetDocPath;
		pTileset->QueryStringAttribute("source", &tilesetDocPath);

		std::stringstream tilesetDocSourcePath;
		tilesetDocSourcePath << basePath << tilesetDocPath;
		LOG(INFO) << "tilesetDocSourcePath: " << tilesetDocSourcePath.str();

		tinyxml2::XMLDocument tilesetDoc;
		tilesetDoc.LoadFile(tilesetDocSourcePath.str().c_str());

		XMLElement* pTilesetNode = tilesetDoc.FirstChildElement("tileset");
		if (pTilesetNode == nullptr) {
			LOG(ERROR) << "pTilesetNode is null";
			return;
		}

		XMLElement* pTilesetImageNode = pTilesetNode->FirstChildElement("image");
		const char* tilesetImageSource;
		pTilesetImageNode->QueryStringAttribute("source", &tilesetImageSource);
		LOG(INFO) << "Tileset: " << firstGid;
		LOG(INFO) << "TilesetImageSource: " << tilesetImageSource;
		std::stringstream tilesetImagePath;
		tilesetImagePath << tilesetsPath << tilesetImageSource;

		SDL_Texture* tilesetTex = SDL_CreateTextureFromSurface(graphics.GetRenderer(), graphics.LoadSurfaceImage(tilesetImagePath.str()));
		this->_tilesets.push_back(Tileset(tilesetTex, firstGid));

		pTileset = pTileset->NextSiblingElement("tileset");
	}

	XMLElement* pLayer = pMapNode->FirstChildElement("layer");
	while (pLayer != nullptr) {
		XMLElement* pLayerData = pLayer->FirstChildElement("data");
		while (pLayerData != nullptr) {
			if (pLayerData->Attribute("encoding", "csv")) {
				std::string layerDataContent = pLayerData->GetText();
				size_t pos = 0;
				std::string delimiter = ",";
				std::vector<int> tileIds;
				while ((pos = layerDataContent.find(delimiter)) != std::string::npos) {
					tileIds.push_back(std::stoi(layerDataContent.substr(0, pos)));
					layerDataContent.erase(0, pos + delimiter.length());
				}
				int tileCounter = 0;
				if (tileIds.size() > 0) {
					for (int tileId : tileIds) {
						//LOG(INFO) << tileId;
						if (tileId == 0) {
							++tileCounter;
						}
						else {
							Tileset tls;
							for (size_t i = 0; i < this->_tilesets.size(); i++)
							{
								if (this->_tilesets[i].firstGid <= tileId) {
									tls = this->_tilesets.at(i);
								}
							}
							if (tls.firstGid == -1) {
								// No tileset found for this tileId
								++tileCounter;
							}
							else {
								// Get the position of the tile in the level
								int xx = 0;
								int yy = 0;
								xx = tileCounter % mapWidth;
								xx *= tileWidth;
								yy += tileHeight * (tileCounter / mapWidth);
								Vector2 finalTilePosition = Vector2(xx, yy);
								// Calculate the position of the tile in the tileset
								int tilesetWidth, tilesetHeight;
								SDL_QueryTexture(tls.texture, nullptr, nullptr, &tilesetWidth, &tilesetHeight);
								//LOG(INFO) << "tilesetWidth: " << tilesetWidth << " tilesetHeight: " << tilesetHeight;
								int tsxx = tileId % (tilesetWidth / tileWidth) - 1;
								tsxx *= tileWidth;
								int tsyy = 0;
								int amt = (tileId / (tilesetWidth / tileWidth));
								tsyy = tileHeight * amt;
								Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);

								Tile tile(tls.texture, Vector2(tileWidth, tileHeight), finalTilePosition, finalTilesetPosition);
								this->_tiles.push_back(tile);
								++tileCounter;
							}
						}
					}
				}
			}
			pLayerData = pLayerData->NextSiblingElement("data");
		}
		pLayer = pLayer->NextSiblingElement("layer");
	}

	LOG(INFO) << "MapFile: " << mapFilePath.str() << "\nMapWidth: " << mapWidth << "\nMapHeight: " << mapHeight
		<< "\nTileWidth: " << tileWidth << "\nTileHeight: " << tileHeight;

}
