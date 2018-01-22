#pragma once
// s'occupe du spawn des wave du minion
// s'assure que get_level_loaded_flag == true
// contient une ref vers les waves a spawn 
// est entièrement controlé par map manager?
// ou plutot controlé par gamemanager pour évtyenullement laisser un temps pour poser les tours
// avant de spawn les ennemis.
// dans tout les cas ce manager s'appuie beaucoup sur MapManager
// et peut-être renoimmé MapManager MapTileManager.
class MapWaveManager
{
public:
	MapWaveManager();
	~MapWaveManager();
};

