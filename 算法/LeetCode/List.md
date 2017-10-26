LRU cache

> 为了使查找、插入和删除都有较高的性能，我们使用一个双向链表（list）和一个哈希表（unordered_map），因为：
>
> * 哈希表保存每个节点的地址，可以基本保证在O（1）时间内查找节点；
>
> * 双向链表插入和删除效率高，单向链表插入和删除时，还要查找节点的前驱节点；
>
>   具体实现细节
>
>   * 越靠近链表头部，表示节点上次访问距离现在时间越短，尾部的节点表示最近访问最少
>   * 访问节点时，如果节点存在，把该节点交换到链表头部，同时更新hash表中该节点的地址
>   * 插入节点时，如果cache的size达到了上限capacity，则删除尾部节点，同时要在hash表中删除对应的项；新节点插入链表头部。

```c++
class LRUCache {
public:
    struct CacheNode{
        int key;
        int val;
        CacheNode(int k, int v): key(k), val(v){}
    };
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) return -1;
        cacheList.splice(cacheList.begin() , cacheList , cacheMap[key]);
        cacheMap[key] = cacheList.begin();
        return cacheMap[key]->val;
    }
    
    void put(int key, int value) {
        if (cacheMap.find(key) == cacheMap.end()){
            if (cacheList.size() == capacity){
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }
            cacheList.push_front(CacheNode(key, value));
            cacheMap[key] = cacheList.begin();
        }
        else{
            cacheMap[key]->val = value;
            cacheList.splice(cacheList.begin() , cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
        }
    }
private:
    list<CacheNode> cacheList;
    unordered_map<int , list<CacheNode>::iterator> cacheMap;
    int capacity;
};
```

