/*
    K-means算法的实现
    数据集：Anuran Calls(MFCCs)
           Number of Instance: 7195
           Numebr of Atributes: 22
    作者：蔡冠羽
*/
#include "iostream"
#include "vector"
#include "fstream"
#include "sstream"
#include "string"
#include "cassert"
#include "ctime"
#include "cmath"

// 质心个数
#define NUMCENTER 10

using namespace std;

// 创建每个样本对应的数据结构
class Instance{
public:
    vector<double> attributes;
    string family, genus, species;
    Instance(){
        attributes.resize(22);
    }
    // 清空数据样本
    void clear(){
        attributes.clear();
        family.clear();
        genus.clear();
        species.clear();
    }
    Instance& operator=(const Instance& ins){
        if(this!=&ins){
            attributes = ins.attributes;
            family = ins.family;
            genus = ins.genus;
            species = ins.species;
        }
        return *this;
    }
};

// 创建每个簇的数据结构
class Cluster{
public:
    Instance center;
    vector<Instance> points;
    void clearPoints(){
        points.clear();
    }
};

// 将字符串数据转化为双浮点数
template<class Type>
Type stringToNum(const string str){
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

// 读取数据集
vector<Instance> read(const string file){
    vector<Instance> dataset;
    Instance instance;
    // 读文件  
    ifstream inFile(file.data(), ios::in);  
    string lineStr;  
    vector<vector<string>> strArray;  
    getline(inFile, lineStr);
    while (getline(inFile, lineStr))  
    {  
        // 打印整行字符串  
        // cout << lineStr << endl;  
        // 存成二维表结构  
        stringstream ss(lineStr);  
        string str;  
        vector<string> lineArray;  
        // 按照逗号分隔  
        int count = 0;
        while (getline(ss, str, ',')){
            if(count < 22){
                instance.attributes[count] = stringToNum<double>(str);
            }
            else{
                switch(count){
                    case 22: instance.family = str; break;
                    case 23: instance.genus = str; break;
                    case 24: instance.species = str;
                }
            }
            count ++;
            if(count == 25) count = 0;
        }
        dataset.push_back(instance);
    } 
    
    return dataset;
}   

// 生成制定范围的随机数
int random(int i, int j, int seed){
    srand(seed * 120);
    return rand()%(j - i) + i;
}

// 随机选择K个质点，初始化K个簇
vector<Cluster> init(int k, vector<Instance> dataset){
    vector<Cluster> clusters(k);
    for(int i = 0; i < k; i++){
        int index = random(0, dataset.size(), i);
        clusters[i].center = dataset[index];
    }

    return clusters;
}

// 计算数据样本和质心之间的欧氏距离
double calDistance(Instance point, Instance center){
    double distance = 0.0;
    for(int i = 0; i < point.attributes.size(); i++){
        distance += pow((point.attributes[i] - center.attributes[i]), 2);
    }
    distance = sqrt(distance);
    return distance;
}

// 将每个数据样本归入距离其最近的质点所在的簇
void findCluster(vector<Cluster>& clusters, Instance point){
    int index = 0;
    double minDist = calDistance(point, clusters[0].center);
    for(int i = 0; i < clusters.size(); i++){
        double tempDist = calDistance(point, clusters[i].center);
        if(minDist > tempDist){
            minDist = tempDist;
            index = i;
        }
    }
    clusters[index].points.push_back(point);
}

// 计算簇的质心（数据样本的均值）
Instance calCenter(Cluster cluster){
    Instance center;
    for(int i = 0; i < cluster.points.size(); i++){
        for(int j = 0; j < cluster.center.attributes.size(); j++){
            center.attributes[j] += cluster.points[i].attributes[j] / (double)cluster.points.size();
        }
    }
    return center;
}

// 计算误差平方和
double calSSE(vector<Cluster> clusters){
    double SSE = 0.0;
    for(int i = 0; i < clusters.size(); i++){
        for(int j = 0; j < clusters[i].points.size(); j++){
            SSE += calDistance(clusters[i].points[j], clusters[i].center);
        }
    }
    return SSE;
}

// K-means聚类算法
vector<Cluster> clustering(vector<Cluster>& clusters, vector<Instance> &dataset){
    double SSE = 0.0;
    while(1){
        for(int i = 0; i < clusters.size(); i++)
            clusters[i].clearPoints();
        for(int i = 0; i < dataset.size(); i++)
            findCluster(clusters, dataset[i]);
        for(int i = 0; i < clusters.size(); i++)
            clusters[i].center = calCenter(clusters[i]);
        double temp = calSSE(clusters);
        if(abs(SSE - temp) <= 1e-3){
            SSE = temp;
            cout << "The final SSE: " << SSE << endl;
            break;
        }
        else
            SSE = temp;
        cout << "SSE: " << SSE << endl;
    }
    return clusters;
}

int main(){
    vector<Instance> dataset;
    vector<Cluster> clusters;
    dataset = read(".\\AnuranCalls(MFCCs)\\Frogs_MFCCs.csv");
    clusters = init(NUMCENTER, dataset);
    clusters = clustering(clusters, dataset);
    return 0;
}