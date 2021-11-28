#include <yaml-cpp/yaml.h>

class IYAMLConfigurable
{
public:
    virtual void ReadInitializationParameters(const YAML::Node& paramsNode) = 0;
};
    