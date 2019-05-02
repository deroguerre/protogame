<b>Room</b>
```cpp
map<string, Tile*>  getDoorTiles()                              //retourne la liste des portes
vector<Rectangle>   getCollisionDoors()                         //retourne le collider de chaque porte
void                setCollisionTiles(vector<int> aTileIds)     //set des collisions à partir d'une liste d'ID tiled
```

<b>TilemapXmlParse</b>

```cpp
Vector2 	    getTilemapSize()                            //retourne la taille de la map en pixel
Vector2             getTileSize()                               //retourne la taille d'une tile
vector<Tileset>     getTilesets()                               //retourne les tilesets sous forme de liste
vector<int>         getTiles()                                  //retourne tous les "gid" tiled de la map
void 		    getTiles(vector<Tile*>* aTiles)             //retourne toutes les tiles sous forme de liste
void 		    getObject(vector<Rectangle>* aRectangles, string aObjectGroupName = string())
void 		    getObject(vector<Vector2>* aPoint, string aObjectGroupName = string())
void 		    getObject(map<string, Rectangle>* aRectangles, string aObjectGroupName = string())
void 		    getObject(map<string, Vector2>* aPoint, string aObjectGroupName = string())
```