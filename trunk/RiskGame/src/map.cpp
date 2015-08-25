
#include "map.h"

#define IO_WriteOnly QIODevice::WriteOnly
#define IO_ReadOnly QIODevice::ReadOnly

Map& Map::getInstance() {
    static Map instance;
    return instance;
}
/**
	Metoda laduje mape z pliku xml
	@param filename nazwa pliku z ktorego ma byc zaladowana mapa
*/
bool Map::loadMap(QString filename){
    mapName_ = filename;
    QTextStream cin(stdin, QIODevice::ReadOnly);
    QTextStream cout(stdout, QIODevice::WriteOnly);
    QTextStream cerr(stderr, QIODevice::WriteOnly);

    territories_.clear();
    continents_.clear();
    #ifndef TESTS
	connections_.clear();
    #endif

    QDomDocument doc( "RiskMap" );
    QFile file( filename );
    if( !file.open( IO_ReadOnly ) )
      return false;
    if( !doc.setContent( &file ) )
    {
      file.close();
      return false;
    }
    file.close();

    QDomElement root = doc.documentElement();
    if( root.tagName() != "map" )
      return false;

    //territoryVect terr;

    // petla pobiera po kolei elementy continent z map
    QDomNode n = root.firstChild();
    while(!n.isNull())
    {
		if(n.toElement().tagName() == "continent")
		{
			int c_bonus_p;
			QString c_name_p;
			idVect c_terr_p;
			territoryVect terr;
	    	
			//pobieranie info z continent
			QDomNode nn = n.firstChild();
			if(nn.toElement().tagName() == "info")
			{
				c_name_p = nn.toElement().attribute( "name", "" );
				c_bonus_p = nn.toElement().attribute( "bonus", "" ).toInt();	
			}
			nn = nn.nextSibling();
	    	
			//petla pobiera po kolei elementy territory
			//i wrzuca je do vektora terytoriow i odpowiedniego kontynentu
			while( !nn.isNull() )
			{
				idVect neighbours_p;
				pointVect points_p;
				int id_p;
				QString name_p;

				//petla pobiera poszczegolne cechy elementu
				QDomNode nnn = nn.firstChild();
				while(!nnn.isNull())
				{
					QDomElement e = nnn.toElement();
					if(!e.isNull())
					{
						if(e.tagName() == "info")
						{
							name_p = e.attribute( "name", "" );
							id_p = e.attribute( "id", "" ).toInt();
							c_terr_p.push_back(id_p);
						}
						else if(e.tagName() == "point")
						{
							QPoint p( e.attribute( "x", "" ).toInt(), e.attribute( "y", "" ).toInt() );
							points_p.push_back(p);
						}
						else if(e.tagName() == "neighbour")
						{
							neighbours_p.push_back(e.attribute( "id", "" ).toInt());
						}
					}
					nnn = nnn.nextSibling();
	    			
				}
				pTerritory t(new Territory(points_p, name_p, neighbours_p, id_p));

				terr.push_back(t);
				territories_.push_back(t);

				nn = nn.nextSibling();
			}
			continents_.push_back(pContinent(new Continent(c_name_p, c_bonus_p, terr)));
		}
		else if(n.toElement().tagName() == "connection")
		{
			QDomNode nn = n.firstChild();
			QPoint p1(nn.toElement().attribute( "x", "" ).toInt(),nn.toElement().attribute( "y", "" ).toInt());
			nn = nn.nextSibling();
			QPoint p2(nn.toElement().attribute( "x", "" ).toInt(),nn.toElement().attribute( "y", "" ).toInt());
            #ifndef TESTS
			pConnection c(pConnection(new TerritoriesConnection(p1,p2)));
			connections_.push_back(c);
            #endif
		}
	    n = n.nextSibling();	
    }
    randomizeStartingPositions();
    return true;
}

/**
	Metoda sluzaca do uzyskania terytorium
	@see Territory
	@param id identyfikator terytorium
	@ return wskaznik na terytorium
*/
pTerritory Map::getTerritory(int id){
    foreach(pTerritory t, territories_)
        if(t->id() == id)
            return t;

    return pTerritory();
}

/**
	Metoda pozwala uzyskac wektor wskaznikow na terytoria danego gracza
	@param id identyfikator zawodnika
	@return wektor wkasnikow na terytoria
*/
territoryVect Map::getPlayerTerritories(PlayerId id) const{
    territoryVect v;
    foreach(pTerritory t, territories_)
        if(t->ownership() == id)
            v.push_back(t);

    return v;
}

int Map::playerStartingPosition(PlayerId id) const{
    return startingPositions[id];
}

void Map::setPlayerStartingPosition(PlayerId id, int pos){
    startingPositions[id] = pos;
}

void Map::setPlayerStartingPositions(){
    pTerritory t;

    for(int i=0; i<NO_PLAYERS; i++){
        t = getTerritory(startingPositions[i]);
        t->setUnit(INFANTRY, STARTING_INFANTRY_PLAYER);
        t->addBuilding(BUNKER);
        t->addBuilding(WATCHTOWER);
        t->addBuilding(FACTORY);
        t->setOwnership(PlayerId(i));
    } 
}

void Map::clearStartingPositions(){
    for(int i=0; i<NO_PLAYERS; i++)
        startingPositions[i] = 0;
}

void Map::randomizeStartingPositions(){

    clearStartingPositions();

    for(int i=0; i<NO_PLAYERS; i++){
        while(true){
            int rand = qrand()%territories_.size();
			++rand;
            bool is = false;

            for(int j=0; j<i; j++){
                if(startingPositions[j] == rand){
                    is = true;
                    break;
                }
            }

            if(!is){
                startingPositions[i] = rand;
                break;
            }
        }
    }
}