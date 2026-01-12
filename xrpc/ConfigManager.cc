#include "ConfigManager.h"
#include "base/cppbase.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

namespace pt = boost::property_tree;

ConfigManager::ConfigManager(const string &config_file)
: config_file_(config_file)
{
    loadConfig();
}

/**
 * 加载配置文件
 */
bool ConfigManager::loadConfig()
{
    try
    {
        pt::ini_parser::read_ini(config_file_, ptree_);
        cout << "load config file: " << config_file_ << endl;
        return true;
    } catch (const pt::ini_parser_error &e)
    {
        cout << "load config file failed: " << e.what() << endl;
        cout << "use default config" << endl;
        createDefaultConfig();
        return false;
    }
}

/**
 * 保存配置文件
 */
bool ConfigManager::saveConfig()
{
    try
    {
        pt::ini_parser::write_ini(config_file_, ptree_);
        cout << "save config file: " << config_file_ << endl;
        return true;
    } catch (const pt::ini_parser_error &e)
    {
        cout << "save config file failed: " << e.what() << endl;
        return false;
    }
}

/**
 * 创建默认配置
 */
void ConfigManager::createDefaultConfig()
{
    // 数据库配置
    setValue("database.host", "localhost");
    setValue("database.port", 3306);
    setValue("database.username", "admin");
    setValue("database.password", "secret");
    setValue("database.name", "myapp_db");

    // 网络配置
    setValue("network.server_ip", "127.0.0.1");
    setValue("network.server_port", 8080);
    setValue("network.timeout", 30);
    setValue("network.max_connections", 100);

    setValue("zookeeper.ip", "127.0.0.1");
    setValue("zookeeper.port", 9999);
    setValue("server.ip", "127.0.0.1");
    setValue("server.port", 8888);

    // 应用配置
    setValue("application.name", "MyApp");
    setValue("application.version", "1.0.0");
    setValue("application.debug_mode", false);
    setValue("application.log_level", "info");

    // 用户界面配置
    setValue("ui.window_width", 1024);
    setValue("ui.window_height", 768);
    setValue("ui.fullscreen", false);
    setValue("ui.language", "zh_CN");

    // 保存默认配置
    saveConfig();
}

/**
 * 获取字符串值
 */
string ConfigManager::getString(const string &key, const string &default_value)
{
    try
    {
        return ptree_.get<string>(key);
    } catch (...)
    {
        return default_value;
    }
}

/**
 * 获取整数值
 */
int ConfigManager::getInt(const string &key, int default_value)
{
    try
    {
        return ptree_.get<int>(key);
    } catch (...)
    {
        return default_value;
    }
}

/**
 * 获取浮点数值
 */
double ConfigManager::getDouble(const string &key, double default_value)
{
    try
    {
        return ptree_.get<double>(key);
    } catch (...)
    {
        return default_value;
    }
}

/**
 * 获取布尔值
 */
bool ConfigManager::getBool(const string &key, bool default_value)
{
    try
    {
        string value = ptree_.get<string>(key);
        return (value == "true" || value == "1" || value == "yes");
    } catch (...)
    {
        return default_value;
    }
}

/**
 * 获取数组/列表
 */
template <typename T> vector<T> ConfigManager::getArray(const string &key)
{
    vector<T> result;
    try
    {
        BOOST_FOREACH (const pt::ptree::value_type &v, ptree_.get_child(key))
        {
            result.push_back(v.second.get_value<T>());
        }
    } catch (...)
    {
        // 返回空数组
    }
    return result;
}

/**
 * 设置值（泛型）
 */
template <typename T> void ConfigManager::setValue(const string &key, const T &value) { ptree_.put(key, value); }

/**
 * 设置数组
 */
template <typename T> void ConfigManager::setArray(const string &key, const vector<T> &values)
{
    pt::ptree array_tree;
    for (const auto &value : values)
    {
        pt::ptree item;
        item.put("", value);
        array_tree.push_back(make_pair("", item));
    }
    ptree_.put_child(key, array_tree);
}

/**
 * 检查配置项是否存在
 */
bool ConfigManager::hasKey(const string &key) { return ptree_.get_optional<string>(key).is_initialized(); }

/**
 * 删除配置项
 */
bool ConfigManager::removeKey(const string &key) { return ptree_.erase(key) > 0; }

/**
 * 获取所有配置项
 */
void ConfigManager::printAllConfig() const
{
    cout << "\n=== 当前配置 ===" << endl;
    printTree("", ptree_);
}

/**
 * 获取特定章节的所有配置
 */
map<string, string> ConfigManager::getSection(const string &section)
{
    map<string, string> result;
    try
    {
        pt::ptree section_tree = ptree_.get_child(section);
        for (const auto &pair : section_tree)
        {
            result[pair.first] = pair.second.data();
        }
    } catch (...)
    {
        // 返回空 map
    }
    return result;
}

void ConfigManager::printTree(const string &prefix, const pt::ptree &tree) const
{
    for (const auto &pair : tree)
    {
        if (pair.second.empty())
        {
            // 叶子节点（配置项）
            cout << prefix << pair.first << " = " << pair.second.data() << endl;
        }
        else
        {
            // 非叶子节点（章节）
            string new_prefix = prefix.empty() ? pair.first + "." : prefix + pair.first + ".";
            printTree(new_prefix, pair.second);
        }
    }
}
