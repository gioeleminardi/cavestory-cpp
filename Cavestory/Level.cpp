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
	//Draw the background
	SDL_Rect sourceRect = {
		0,
		0,
		64,
		64
	};

	SDL_Rect destRect;
	for (int x = 0; x < this->_mapSize.x / sourceRect.w; x++)
	{
		for (int y = 0; y < this->_mapSize.y / sourceRect.h; y++)
		{
			destRect.x = x * sourceRect.w * Globals::SPRITE_SCALE;
			destRect.y = y * sourceRect.h * Globals::SPRITE_SCALE;
			destRect.w = sourceRect.w * Globals::SPRITE_SCALE;
			destRect.h = sourceRect.h * Globals::SPRITE_SCALE;
			graphics.BlitSurface(this->_backgroundTexture, &sourceRect, &destRect);
		}
	}
}

void Level::LoadMap(std::string mapName, Graphics & graphics)
{
	//TEMPORARY CODE TO LOAD THE BACKGROUND
//	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.GetRenderer(),
//		graphics.LoadSurfaceImage(".//content//backgrounds//bkBlue.png"));
//
//	this->_mapSize = Vector2(Globals::SCREEN_WIDTH * 2, Globals::SCREEN_HEIGHT * 2);

    std::string basePath = ".//content//maps//";
    std::stringstream mapFilePath;
    mapFilePath << basePath << mapName << ".tmx";

    XMLDocument doc;
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

    if (pTileset != nullptr){
        while(pTileset){
            int firstGid;
            pTileset->QueryIntAttribute("firstgid", &firstGid);

            const char* tilesetDocPath;
            pTileset->QueryStringAttribute("source", &tilesetDocPath);
            std::stringstream tilesetDocSourcePath;
            tilesetDocSourcePath << basePath << tilesetDocPath;
            LOG(INFO) << "tilesetDocSourcePath: " << tilesetDocSourcePath.str();
            XMLDocument tilesetDoc;
            tilesetDoc.LoadFile(tilesetDocSourcePath.str().c_str());
            XMLElement* pTilesetNode = doc.FirstChildElement("tileset");
            if(pTilesetNode == nullptr){
                LOG(ERROR) << "pTilesetNode is null";
            }
//            XMLElement* pTilesetImageNode = pTilesetNode->FirstChildElement("image");
//            const char* tilesetImageSource;
//            pTilesetImageNode->QueryStringAttribute("source", &tilesetImageSource);

            LOG(INFO) << "Tileset: " << firstGid;
//            LOG(INFO) << "TilesetImageSource: " << tilesetImageSource;

            pTileset = pTileset->NextSiblingElement("tileset");
        }
    }





    LOG(INFO) << "MapFile: " << mapFilePath.str() << "\nMapWidth: " << mapWidth << "\nMapHeight: " << mapHeight
              << "\nTileWidth: " << tileWidth << "\nTileHeight: " << tileHeight;


}
