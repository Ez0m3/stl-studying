#include<iostream>
#include<string>
#include<vector>
#include<fstream>
class person
{
    public:
    std::string name;
    int age;
    person(std::string name1,int age1):name(name1),age(age1){}
};
void infile(std::vector<person>& ps)
{
    std::ifstream ifs("info.txt");
    if(!ifs.is_open())
    {
        std::cout<<"无法打开文件读取数据！"<<std::endl;
        return;
    }
    std::string name;
    int age;
    while(ifs>>name>>age)
    {
        ps.push_back(person(name,age));
    }
    ifs.close();
    std::cout<<"从文件读取数据成功"<<std::endl;
}
void outfile(const std::vector<person>& ps)
{
    std::ofstream ofs("info.txt");
    if(!ofs.is_open())
    {
        std::cerr<<"无法打开文件写入数据！"<<std::endl;
        return;
    }
    for(const auto& p:ps)
    {
        ofs<<p.name<<" "<<p.age<<"\n";
    }
    ofs.close();
    std::cout<<"文件已成功写入数据"<<std::endl;
}
void test()
{
    std::vector<person> ps;
    infile(ps);
    ps.push_back(person("hwx",24));
    ps.push_back(person("cjw",23));
    ps.push_back(person("micu",7));
    ps.push_back(person("baozi",6));
    ps.push_back(person("duncu",5));
    outfile(ps);
}      
int main()
{
    test();
    std::cout<<std::endl;
    return 0;   
}