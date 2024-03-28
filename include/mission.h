#ifndef MISSION_H
#define MISSION_H

#include "map.h"
#include "config.h"
#include "xmlLogger.h"
#include "searchresult.h"
#include "aa_sipp.h"
#include "task.h"
#include "dynamicobstacles.h"

class Mission
{
public:
    Mission();
    ~Mission();

    bool getMap();
    bool getTask();
    bool getConfig();
    bool getObstacles();
    void createLog();
    void createSearch();
    void startSearch();
    void printSearchResultsToConsole();
    void saveSearchResultsToLog();
    void setFileNames(const std::string taskName, const std::string mapName, const std::string configName, const std::string obstaclesName);

private:
    Map              m_map;
    Task             m_task;
    Config           m_config;
    DynamicObstacles m_obstacles;
    AA_SIPP*         m_pSearch;
    XmlLogger*       m_pLogger;
    SearchResult     sr;
    std::string mapName;
    std::string taskName;
    std::string configName;
    std::string obstaclesName;

};

#endif

