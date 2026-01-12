#include <string>
#include <vector>
#include <map>
#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

class ConfigManager
{
public:
    explicit ConfigManager(const std::string &config_file = "config.ini");

    /**
     * 加载配置文件
     */
    bool loadConfig();

    /**
     * 保存配置文件
     */
    bool saveConfig();

    /**
     * 创建默认配置
     */
    void createDefaultConfig();

    /**
     * 获取字符串值
     */
    std::string getString(const std::string &key, const std::string &default_value = "");

    /**
     * 获取整数值
     */
    int getInt(const std::string &key, int default_value = 0);

    /**
     * 获取浮点数值
     */
    double getDouble(const std::string &key, double default_value = 0.0);

    /**
     * 获取布尔值
     */
    bool getBool(const std::string &key, bool default_value = false);

    /**
     * 获取数组/列表
     */
    template <typename T> std::vector<T> getArray(const std::string &key);

    /**
     * 设置值（泛型）
     */
    template <typename T> void setValue(const std::string &key, const T &value);

    /**
     * 设置数组
     */
    template <typename T> void setArray(const std::string &key, const std::vector<T> &values);

    /**
     * 检查配置项是否存在
     */
    bool hasKey(const std::string &key);

    /**
     * 删除配置项
     */
    bool removeKey(const std::string &key);

    /**
     * 获取所有配置项
     */
    void printAllConfig() const;

    /**
     * 获取特定章节的所有配置
     */
    std::map<std::string, std::string> getSection(const std::string &section);

    void printTree(const std::string &prefix, const pt::ptree &tree) const;

private:
    pt::ptree ptree_;
    std::string config_file_;
};