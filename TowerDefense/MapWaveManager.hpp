#pragma once
// s'occupe du spawn des wave du minion
// s'assure que get_level_loaded_flag == true
// contient une ref vers les waves a spawn 
// est enti�rement control� par map manager?
// ou plutot control� par gamemanager pour �vtyenullement laisser un temps pour poser les tours
// avant de spawn les ennemis.
// dans tout les cas ce manager s'appuie beaucoup sur MapManager
// et peut-�tre renoimm� MapManager MapTileManager.
class MapWaveManager
{
public:
	MapWaveManager();
	~MapWaveManager();
};

