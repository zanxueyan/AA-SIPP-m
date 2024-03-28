#include"mission.h"

Mission::Mission()
{
    m_pSearch = nullptr;
    m_pLogger = nullptr;
}

Mission::~Mission()
{
    delete m_pSearch;
    delete m_pLogger;
}

void Mission::setFileNames(const std::string task_name, const std::string map_name, const std::string config_name, const std::string obstacles_name)
{
    this->mapName = map_name;
    this->taskName = task_name;
    this->configName = config_name;
    this->obstaclesName = obstacles_name;
}

bool Mission::getMap()
{
    return m_map.getMap(mapName.c_str());
}

bool Mission::getTask()
{
    return (m_task.getTask(taskName.c_str()) && m_task.validateTask(m_map));
}

bool Mission::getConfig()
{
    return m_config.getConfig(configName.c_str());
}

bool Mission::getObstacles()
{
    if(obstaclesName!="")
        return m_obstacles.getObstacles(obstaclesName.c_str());
    else
        return false;
}

void Mission::createSearch()
{
    if(m_pSearch)
    {
        delete m_pSearch;
        delete m_pLogger;
    }
    m_pSearch = new AA_SIPP(m_config);
}

void Mission::createLog()
{
    if(m_config.loglevel != CN_LOGLVL_NO)
    {
        m_pLogger = new XmlLogger(m_config.loglevel);
        m_pLogger->createLog(taskName.c_str());
    }
}

void Mission::startSearch()
{
    //std::cout<<"SEARCH STARTED\n";
    sr = m_pSearch->startSearch(m_map, m_task, m_obstacles);
}

void Mission::printSearchResultsToConsole()
{
    //std::cout<<bool(sr.agentsSolved/sr.agents)<<" "<<sr.time<<" "<<sr.makespan<<" "<<sr.pathlength<<" "<<sr.flowlength<<"\n";
    std::cout<<"Results:\nTask solved: "<<bool(sr.agentsSolved/sr.agents)<<"\nTries: "<<sr.tries<<"\nRuntime: "<<sr.runtime<<"\nAgents solved: "<<sr.agentsSolved<<" ("<<(float)sr.agentsSolved*100/sr.agents<<"%)\nFlowtime: "<<sr.flowtime<<"\nMakespan: "<<sr.makespan<<"\n";
}

void Mission::saveSearchResultsToLog()
{
    if(m_config.loglevel == CN_LOGLVL_NO)
        return;
    std::cout<<"LOG STARTED\n";
    m_pLogger->writeToLogInput(taskName.c_str(), mapName.c_str(), configName.c_str(), obstaclesName.c_str());
    m_pLogger->writeToLogSummary(sr);
    if(sr.pathfound)
    {
        m_pLogger->writeToLogMap(m_map, sr);
        m_pLogger->writeToLogPath(sr, m_task, m_config);
    }
    m_pLogger->saveLog();
    std::cout<<"LOG SAVED\n";
}

