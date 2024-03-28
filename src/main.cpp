#include"mission.h"
#include <iostream>

int main(int argc, char* argv[])
{
    //设定对应文件路径
    const std::string mapName = "./Instances/Examples/map_example.xml";
    const std::string taskName = "./Instances/Examples/task_example.xml";
    const std::string configName = "./Instances/Examples/config_example.xml";
    const std::string obstaclesName = "./Instances/Examples/obstacles_example.xml";

    Mission mission;
    mission.setFileNames(taskName, mapName, configName, obstaclesName);

    if (!mission.getConfig())
        return 0;
    else
        std::cout<<"CONFIG LOADED\n";

    if (!mission.getMap())
    {
        std::cout<<"Program terminated.\n";
        return 0;
    }
    else
        std::cout<<"MAP LOADED\n";
    if (!mission.getTask())
    {
        std::cout<<"Program terminated.\n";
        return 0;
    }
    else
        std::cout<<"TASK LOADED\n";
    if(mission.getObstacles())
    {
        std::cout<<"OBSTACLES LOADED\n";
    }
    mission.createSearch();
    mission.createLog();
    mission.startSearch();
    mission.printSearchResultsToConsole();
    mission.saveSearchResultsToLog();
 
    return 1;
}
