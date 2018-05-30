# Kmeans #
## 功能 ##
> 在AnuranCalls(MFCCs)数据集上实现K-means算法

## 数据集 ##
> 数据集：AnuranCalls(MFCCs)
> * Number of Instance: 7195
> * Number of Attributes: 22

## 算法步骤 ##
> 1. 读取数据，得到所有无标签的数据样本
> 2. 创建K个点作为起始质点（随机选择)
> 3. 计算每个样本和质点间的距离，将样本归到距其最近的质心所在的簇
> 4. 计算每个簇的新质点（计算簇内样本的平均值）
> 5. 判断误差平方和是否变化，若变化回到3，若不变化退出算法

## 结果 ##
> 在K=10时，误差平方和为14602.1.

## API ##
> `vector<Instance> read(const string file)`:  
> 读取数据集  
> @param: const string file: 数据集文件的路径字符串  
> @return: 数据

> `int random(int i, int j, int seed)`:  
> 产生随机数  
> @param: int i: 随机数范围的最小值（包括）  
> @param: int j: 随机数范围的最大值（不包括）  
> @param: int seed: 随机数种子  
> @return: 随机数  

> `vector<Cluster> init(int k, vector<Instance> dataset)`:  
> 随机选择K个质点，初始化K个簇  
> @param: int k: 质点个数  
> @param: vector<Instance> dataset: 数据集  
> @return: K个以随机选取的数据样本为质心的簇  

> `double calDistance(Instance point, Instance center)`:  
> 计算数据样本和质心的欧氏距离  
> @param: Instance point: 数据样本  
> @param: Instance center: 簇的质心  
> @return: 计算得到的欧式距离  

> `void findCluster(vector<Cluster>& clusters, Instance point)`:  
> 将每个数据样本归入距其最近的质心所在的簇  
> @param: vector<Cluster>& clusters: 所有簇的向量引用  
> @param: Instance point: 需要归入簇的数据样本  
> @return: 

> `Instance calCenter(Cluster cluster)`:  
> 计算簇的质心  
> @param: Cluster cluster: 需要计算质心的簇  
> @return: 簇的质心  

> `double calSSE(vector<Cluster> clusters)`:  
> 计算误差平方和  
> @param: vector<Cluster> clusters: 所有簇的向量  
> @return: 误差平方和  

> `vector<Cluster> clustering(vector<Cluster>& clusters, vector<Instance> &dataset)`:  
> K-means聚类算法  
> @param: vector<Cluster>& clusters: 初始化的K个簇组成的向量  
> @param: vector<Instance>& dataset: 所有的数据样本  
> @return: 聚类完成的K个簇