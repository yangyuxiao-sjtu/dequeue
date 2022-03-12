#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"
#include <iostream>
#include <cstddef>
#include <cmath>
const int NN=150*150;
namespace sjtu { 
template<class T>
class deque {
private:
       struct node{
            T **p;
            node* next;
            node *last;
            int now_size;
        };
        node *first,*ed,*now_pos;
        int *deque_type;
        int n,total_num;
public:
    class const_iterator;
    class iterator {
    public:
        node *position;
        int pos_num;
        int *type;
    public:
        iterator(node * pp=nullptr, int nn=0,int *type_name=nullptr){
            position= pp;
            pos_num=nn;
            type = type_name; 
        }
        iterator(const iterator & other){
            position = other.position;
            pos_num=other.pos_num;
            type = other.type;
        }
        iterator& operator =(const iterator & other){
            position = other.position;
            pos_num=other.pos_num;
            type = other.type;
            return *this;
        }
        iterator  operator+(const long long   &add_n)  const {
            iterator tmp(position,pos_num,type); 
            if(add_n==0) return *this;
            long long  count= add_n;
            if(add_n>=0){ 
            while(count-((tmp.position)->now_size-tmp.pos_num-1)>0){
            if(tmp.position->next == nullptr){
            if(tmp.position->now_size==*type){
                    tmp.position->next=new node;
                    tmp.position->next->p= new T*[*type];
                    tmp.position=tmp.position->next;
                    tmp.pos_num=0;
                    tmp.position->next=nullptr;
                    tmp.position->now_size=0;
                }
                else tmp.pos_num=tmp.position->now_size;
                return tmp;
            }
            count-=(tmp.position->now_size-tmp.pos_num-1);
            tmp.position = tmp.position->next;
             tmp.pos_num=-1;
            }
            tmp.pos_num=count+tmp.pos_num;
            }
            else{
                while(count+ tmp.pos_num<0){
                    count +=tmp.pos_num;
                    tmp.position=tmp.position->last;
                    if(tmp.position==nullptr)throw("out_of_bound");
                    tmp.pos_num= tmp.position->now_size;
                    
                }
                tmp.pos_num=tmp.pos_num+count;
                if(tmp.pos_num==*tmp.type){
                    tmp.position=tmp.position->next;
                    tmp.pos_num=0;
                }
            }        
            return tmp;  
        }
        iterator operator-(const long long &n) const {
            iterator tmp= *this+(-1*n);
            return tmp;
        }
        // return th distance between two iterator,
        // if these two iterators points to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            if(type!=rhs.type)throw("invaild_iterator");
            iterator tmp={this->position,this->pos_num,this->type};
            int count =0;
            while(tmp.position){
                    if(tmp.position!=rhs.position){
                        count-=tmp.position->now_size-tmp.pos_num-1;
                        tmp.position = tmp.position->next;
                        tmp.pos_num=-1;
                    }
                    else {
                        count += tmp.pos_num - rhs.pos_num;
                        return count ;
                    }
            }
            count =0;
            tmp = rhs;
            while(tmp.position!=nullptr){
                if(tmp.position!= position ){
                    count += tmp.position->now_size -tmp.pos_num -1;
                    tmp.position=tmp.position->next;
                    tmp.pos_num=-1;
                }
                else {
                    count +=pos_num - (tmp.pos_num);
                    return count ;
                }
            }
        }
        iterator& operator+=(const int &add_n) { 
            if(add_n==0) return *this;
            long long  count= add_n;
            if(add_n>=0){ 
            while(count-((position)->now_size-pos_num-1)>0){
            if(position->next == nullptr){
            if(position->now_size==*type){
                    position->next=new node;
                    position->next->p= new T*[*type];
                    position=position->next;
                    pos_num=0;
                    position->next=nullptr;
                    position->now_size=0;
                }
                else pos_num=position->now_size;
                return *this;
            }
            count-=position->now_size-pos_num-1;
            position = position->next;
             pos_num=-1;
            }
            pos_num=count+pos_num;
            }
            else{
                while(count+ pos_num<0){
                    count +=pos_num;
                    position=position->last;
                    if(position==nullptr)
                    throw("out_of_bound");
                    pos_num= position->now_size; 
                }
                pos_num=pos_num+count;
                if(pos_num==*type){
                    position=position->next;
                    pos_num=0;
                }
            }        
            return *this;  
        }
        iterator& operator-=(const long long &n) {
            return *this+=(-1*n);
        }
        iterator operator++(int) {
            iterator tmp=*this;
            *this+=1;
            return  tmp; 
        }
        iterator& operator++() {
            *this+=1;
            return *this;
        }
        iterator operator--(int) {
            iterator tmp= *this;
            *this-=1;
            return tmp;
        }
        iterator& operator--() {
            *this-=1;
            return *this;
        }
        T& operator*() const {
            if(pos_num>=position->now_size)throw("invalid_operator");
            return *(position->p[pos_num]);
        } 
        T* operator->() const noexcept {
            return position->p[pos_num];
        }
        bool operator==(const iterator &rhs) const {
            if((type==rhs.type)&&(position==rhs.position)&&(pos_num==rhs.pos_num))return 1;
            return 0;
        }
        bool operator==(const const_iterator &rhs) const {
            if((type==rhs.type)&&(position==rhs.position)&&(pos_num==rhs.pos_num))return 1;
            return 0;
        }
        bool operator!=(const iterator &rhs) const {return !(*this==rhs);}
        bool operator!=(const const_iterator &rhs) const {return !(*this==rhs);}
        ~iterator(){
            position = nullptr;
            type = nullptr;
            pos_num=0;
        }
    };
    class const_iterator {
        
        public:
        node *position;
        int pos_num;
        int *type;
        public:
            const_iterator(node * pp=nullptr, int nn=0,int *type_name=nullptr){
            position= pp;
            pos_num=nn;
            type = type_name;
            }
            const_iterator(const const_iterator &other) {
                position = other.position;
                type= other.type;
                pos_num= other.pos_num;            
            }
            const_iterator(const iterator &other) {
                position = other.position;
                type= other.type;
                pos_num= other.pos_num; 
            }
            T& operator*() const {
            if(position->p[pos_num]==nullptr)throw("invalid_operator");
            return *(position->p[pos_num]);
        } 
        ~const_iterator(){
            position = nullptr;
            pos_num =0;
            type =nullptr;
        }
        T* operator->() const noexcept {
            return position->p[pos_num];
        }
        bool operator==(const iterator &rhs) const {
            if(type==rhs.type&&position==rhs.position&&pos_num==rhs.pos_num)return 1;
            return 0;
        }
        bool operator==(const const_iterator &rhs) const {
            if(type==rhs.type&&position==rhs.position&&pos_num==rhs.pos_num)return 1;
            return 0;
        }
        bool operator!=(const iterator &rhs) const {return !(*this==rhs);}
        bool operator!=(const const_iterator &rhs) const {return !(*this==rhs);}
        const_iterator operator =(const iterator & other){
            position = other.position;
            pos_num=other.pos_num;
            type = other.type;
        }
        const_iterator  operator+(const long long   &add_n)  const {
            const_iterator tmp(position,pos_num,type); 
            if(add_n==0) return *this;
            long long  count= add_n;
            if(add_n>=0){ 
            while(count-((tmp.position)->now_size-tmp.pos_num-1)>0){
            if(tmp.position->next == nullptr){
            if(tmp.position->now_size==*type){
                    tmp.position->next=new node;
                    tmp.position->next->p= new T*[*type];
                    tmp.position=tmp.position->next;
                    tmp.pos_num=0;
                    tmp.position->next=nullptr;
                    tmp.position->now_size=0;
                }
                else tmp.pos_num=tmp.position->now_size;
                return tmp;
            }
            count-=(tmp.position->now_size-tmp.pos_num-1);
            tmp.position = tmp.position->next;
             tmp.pos_num=-1;
            }
            tmp.pos_num=count+tmp.pos_num;
            }
            else{
                while(count+ tmp.pos_num<0){
        ///??
                    count +=tmp.pos_num;
                    tmp.position=tmp.position->last; 
                    if(tmp.position==nullptr)throw("out_of_bound");
                    tmp.pos_num= tmp.position->now_size;
                   
                }
                tmp.pos_num=tmp.pos_num+count;
                if(tmp.pos_num==*tmp.type){
                    tmp.position=tmp.position->next;
                    tmp.pos_num=0;
                }
            }        
            return tmp;  
        }
        const_iterator operator-(const long long &n) const {
            const_iterator tmp= *this+(-1*n);
            return tmp;
        }
        int operator-(const const_iterator &rhs) const {
            if(type!=rhs.type)throw("invaild_iterator");
            const_iterator tmp={this->position,this->pos_num,this->type};
            int count =0;
            while(tmp.position){
                    if(tmp.position!=rhs.position){
                        count-=tmp.position->now_size-tmp.pos_num-1;
                        tmp.position = tmp.position->next;
                        tmp.pos_num=-1;
                    }
                    else {
                        count += tmp.pos_num - rhs.pos_num;
                        return count ;
                    }
            }
            count =0;
            tmp = rhs;
            while(tmp.position!=nullptr){
                if(tmp.position!= position ){
                    count += tmp.position->now_size -tmp.pos_num -1;
                    tmp.position=tmp.position->next;
                    tmp.pos_num=-1;
                }
                else {
                    count +=pos_num - (tmp.pos_num);
                    return count ;
                }
            }
        }
    const_iterator& operator+=(const int &add_n) { 
            if(add_n==0) return *this;
            long long  count= add_n;
            if(add_n>=0){ 
            while(count-((position)->now_size-pos_num-1)>0){
            if(position->next == nullptr){
            if(position->now_size==*type){
                    position->next=new node;
                    position->next->p= new T*[*type];
                    position=position->next;
                    pos_num=0;
                    position->next=nullptr;
                    position->now_size=0;
                }
                else pos_num=position->now_size;
                return *this;
            }
            count-=position->now_size-pos_num-1;
            position = position->next;
            pos_num=-1;
            }
            pos_num=count+pos_num;
            }
            else{
                while(count+ pos_num<0){
                    count +=pos_num;
                    position=position->last;
                    if(position==nullptr)throw("out_of_bound");
                    pos_num= position->now_size;
                }
                pos_num=pos_num+count;
                if(pos_num==*type){
                    position=position->next;
                    pos_num=0;
                }
            }        
            return *this;  
        }
        const const_iterator& operator-=(const long long &n) {
            return *this+=(-1*n);
        }
        const_iterator operator++(int) {
            iterator tmp=*this;
            *this+=1;
            return  tmp; 
        }
        const const_iterator& operator++() {
            *this+=1;
            return *this;
        }
        const_iterator operator--(int) {
            iterator tmp= *this;
            *this-=1;
            return tmp;
        }
        const const_iterator& operator--() {
            *this-=1;
            return *this;
        }
    };
 
    deque(int num=NN):n(num){
        n=sqrt(n)+1;
        first= new node;
        deque_type = new int(n);
        first->next=nullptr;
        first->last=nullptr;
        first->p = new T*[n];
        first->now_size=0;
        total_num=0;
        ed=first;
    }
    deque(const deque &other) {
        node *tmp;
        node *pos=first;
        deque_type= new int(other.n);
        n=other.n;
        total_num=other.total_num;
        pos=other.first;
        first=nullptr;
        ed=nullptr;
        tmp=nullptr;
        while(pos!=nullptr){
            ed=new node;
            ed->last=ed->next=nullptr;
            if(tmp!=nullptr)tmp->next=ed,ed->last=tmp;
            ed->p= new T*[n];
            ed->now_size=pos->now_size;
            for(int i=0;i<ed->now_size;i++){
                ed->p[i]=new T(*(pos->p[i]));
            }
            if(first==nullptr)first=ed;
            pos=pos->next;
            tmp=ed;
        }
    }
    /**
     * TODO Deconstructor
     */
    void DELETE(T** &pp ,int tot){
        for(int i=0;i<tot;i++){
            delete pp[i];
            pp[i]=nullptr;
        }
        delete []pp;
        pp=nullptr;
    }
    ~deque() {
        node *tmp;
        node *pos=first;
        while(pos!=nullptr){
            tmp=pos;
            pos=pos->next;
            DELETE(tmp->p,tmp->now_size);
            delete tmp;
        }
        first=ed=now_pos=nullptr;
        n=0;
        delete deque_type;
        deque_type=nullptr;
        total_num=0;
    }
    /**
     * TODO assignment operator
     */
    deque &operator=(const deque &other) {
        if(&other==this)return *this;
        node *tmp;
        node *pos=first;
        while(pos!=nullptr){
            tmp=pos;
            pos=pos->next;
            DELETE(tmp->p,tmp->now_size);
            delete tmp;
        }
        first=ed=now_pos=nullptr;
        tmp=nullptr;
        pos=other.first;
        n=other.n;
        total_num=other.total_num;
        while(pos!=nullptr){
            ed=new node;
            ed->last=ed->next=nullptr;
            ed->now_size=0;
            ed->p=nullptr;
            if(tmp!=nullptr)tmp->next=ed,ed->last=tmp;
            ed->p= new T*[n];
            ed->now_size=pos->now_size;
            for(int i=0;i<ed->now_size;i++){
                ed->p[i]=new T (*(pos->p[i]));
            }
            if(first==nullptr)first=ed;
            pos=pos->next;
            tmp=ed;
        }
        return *this;
    }
    /**
     * access specified element with bounds checking
     * throw index_out_of_bound if out of bound.
     */
    T & at(const long long  &pos) {
        if(pos<0)throw("index_out_of_bound");
        now_pos=first;
        long long  count=pos+1;
        while(now_pos!=nullptr){
            if(count>now_pos->now_size)count-=now_pos->now_size,now_pos=now_pos->next;
            else{
                return *(now_pos->p[count-1]);
            }
        }
        throw("index_out_of_bound");
    }
    const T & at(const long long &pos) const {
        if(pos<0)throw("index_out_of_bound");
        node *pp=first;
        int count=pos+1;
        while(pp!=nullptr){
            if(count-pp->now_size>0)count-=pp->now_size,pp=pp->next;
            else{
                return *(pp->p[count-1]);
            }
        }
        throw("index_out_of_bound");
    }
    T & operator[](const int &pos) {
        if(pos<0)throw("index_out_of_bound");
        now_pos=first;
        int count=pos+1;
        while(now_pos!=nullptr){
            if(count-now_pos->now_size>0)count-=now_pos->now_size,now_pos=now_pos->next;
            else{
                return *(now_pos->p[count-1]);
            }
        }
        throw("index_out_of_bound");

    }
    const T & operator[](const int &pos) const {
        if(pos<0)throw("index_out_of_bound");
        node *pp=first;
        int count=pos+1;
        while(pp!=nullptr){
            if(count-pp->now_size>0)count-=pp->now_size,pp=pp->next;
            else{
                return *(pp->p[count-1]);
            }
        }
        throw("index_out_of_bound");
    }
    /**
     * access the first element
     * throw container_is_empty when the container is empty. 
     */
    const T & front() const {
            if(total_num==0)throw("container_is_empty");
            else return *first->p[0];
    }
    /**
     * access the last element
     * throw container_is_empty when the container is empty.
     */
    const T & back()  {
        while(ed->next)ed=ed->next;
        if(total_num==0)throw("container_is_empty");
        if(ed->now_size) return *ed->p[ed->now_size-1];
        else return *ed->last->p[ed->last->now_size -1];
    }
    iterator begin() {
        return  iterator{first,0,deque_type};
    }
    const_iterator cbegin() const {
       return  const_iterator{first,0,deque_type};
    }
    /**
     * returns an iterator to the end.
     */
    iterator end() {
        while(ed->next)ed=ed->next;
        if(ed->now_size==n){
            ed->next=new node;
            ed->next->p= new T*[n];
            ed->next->now_size=0;
            ed->next->last =ed;
            ed=ed->next;
            ed->next=nullptr;
        }
        return  iterator{ed,ed->now_size,deque_type};
    }
     const_iterator cend()  const {
        //while(ed->next)ed=ed->next;
        node *tmp= ed;
        while(tmp->next)tmp=tmp->next;
        if(tmp->now_size==n){
            tmp->next=new node;
            tmp->next->p= new T*[n];
            tmp->next->last =tmp;
            tmp->next->now_size=0;
            tmp=tmp->next;
            tmp->next=nullptr;
        }
        return  const_iterator(tmp,tmp->now_size,deque_type);
    }
    /**
     * checks whether the container is empty.
     */
    bool empty() const {
        if(total_num)return 0;
        else return 1;
    }
    /**
     * returns the number of elements
     */
    size_t size() const {
        return total_num;
    }
    /**
     * clears the contents
     */
    void clear() {
        node *pos =first;
        total_num=0;
        node *tmp;
        while(pos!=nullptr){
            tmp=pos;
            pos=pos->next;
            DELETE(tmp->p,tmp->now_size);
            delete tmp;
        }
        first=ed=now_pos=nullptr;
        first= new node;
        first->last=first->next=nullptr;
        first->now_size=0;
        first->p = new T*[n];
        ed=first;

    }
    /**
     * inserts elements at the specified locat on in the container.
     * inserts value before pos
     * returns an iterator pointing to the inserted value
     *     throw if the iterator is invalid or it point to a wrong place.
     */
    node *split(node *tmp_pos){
        node *tmp;
        
        tmp= new node;
        tmp->p= new T*[n];
        tmp->now_size=0;
        tmp->next=tmp->last=nullptr;
        tmp->next=tmp_pos->next;
        tmp_pos->next=tmp;
        tmp->last=tmp_pos;
        if(tmp->next!=nullptr)(tmp->next)->last=tmp;
       while(ed->next)ed=ed->next;
        return tmp;
    }
    node *merge(node *lst_pos,node *pos){
        while(ed->next)ed=ed->next;
        if(lst_pos==pos)return pos;
        for(int i=0;i<pos->now_size;i++){
            lst_pos->p[lst_pos->now_size]=pos->p[i];
            pos->p[i]=nullptr;
            lst_pos->now_size+=1;
        }
        pos->now_size=0;
        DELETE(pos->p,pos->now_size);
        lst_pos->next=pos->next;
        if(lst_pos->next!=nullptr)(lst_pos->next)->last=lst_pos;
        pos->last=pos->next=nullptr;
        if(pos==ed) ed=lst_pos;
        delete pos;
        return lst_pos;
    }
    iterator insert(iterator pos, const T &value) {
            if(pos.type!=deque_type)throw("Invalid_operator");
            node *tmp;
            total_num++;
            tmp = split(pos.position);
            int nn= pos.pos_num;
            int cntt=0;
            for(int i=pos.pos_num;i<pos.position->now_size;i++){
                tmp->p[i-nn]=pos.position->p[i];
               pos.position->p[i]=nullptr;
                cntt++;
                tmp->now_size++;
            }
            pos.position->now_size -=cntt;

            if(pos.position->now_size==n){
                pos.position=pos.position->next;
                pos.pos_num=0;
            }
            pos.position->p[pos.pos_num]=new T(value);
            (pos.position)->now_size = pos.pos_num+1;
            tmp= pos.position->next;
            if(tmp==nullptr)return tmp;
            if(tmp->now_size+pos.position->now_size <=n)
            merge(pos.position,tmp);
            return pos;

    }
    /**
     * removes specified element at pos.
     * removes the element at pos.
     * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
     * throw if the container is empty, the iterator is invalid or it points to a wrong place.
     */
    iterator erase(iterator pos) {
        if(total_num==0)throw("invalid_operation");
        total_num--;
        node *tmp = pos.position;
        bool jud_size= 0;
        delete tmp->p[pos.pos_num];
        for(int i= pos.pos_num;i<tmp->now_size;i++){
            tmp->p[i]=nullptr;
            if(i+1<tmp->now_size){
                tmp->p[i]=tmp->p[i+1];
                jud_size=1;
            }
        }
        tmp->now_size--;
        if(tmp->next!=nullptr){
            if(tmp->now_size+tmp->next->now_size<=n){
                tmp = merge(tmp,tmp->next);
            }
        }
        else if(tmp->last !=nullptr){
            int sz = tmp->last->now_size;
            
            if(tmp->now_size+tmp->last->now_size<=n/2 || tmp->now_size ==0|| tmp->last->now_size ==0){
                tmp = merge(tmp->last,tmp);
                pos.position= tmp;
                pos.pos_num=sz+pos.pos_num;// pos.pos_num=sz+pos.pos_num-1;
                if(jud_size)return pos;
                else {
                    if(pos.position->next== nullptr)return end();
                    else {
                        pos.position = pos.position->next;
                        pos.pos_num =0;
                    }
                }
            }
        }
        if(pos.position->p[pos.pos_num]!=nullptr|| pos==end()) 
        return pos;
        else {
            while(pos.position->p[pos.pos_num]==nullptr){
                if(pos.pos_num >= pos.position->now_size){
                    pos.position = pos.position->next;
                    pos.pos_num=0;
                }
                else pos.pos_num+=1;
                if(pos==end())return pos;
            }
            return pos;
        }
    }
    void push_back(const T &value) {
        while(ed->next)ed=ed->next;
        if(ed->now_size==n)ed=split(ed);
        ed->p[ed->now_size]=new T(value);
        ed->now_size++;
        total_num++;
    }
    /**
     * removes the last element
     *     throw when the container is empty.
     */
    void pop_back() {
        while(ed->next)ed=ed->next;
        if(total_num==0)throw("the container is empty");
        ed->now_size--;
        delete ed->p[ed->now_size];
        total_num--;
        if(ed->last!=nullptr){
            if((ed->last)->now_size+ed->now_size<=n){
                ed=merge(ed->last,ed);
            }
        }
    }
    void push_front(const T &value) {
        if(first->now_size==n){
             node *tmp=new node;
            tmp->p = new T*[n];
            tmp->next=first;
            first->last=tmp;
            tmp->last=nullptr;
            tmp->now_size =1;
            tmp->p[0]= new T(value);
            first= tmp;
            total_num++;
        }
        else{
            for(int i=first->now_size-1;i>=0;i--){
                first->p[i+1]=first->p[i];
                first->p[i]=nullptr;
            }
            first->p[0]=new T(value);
            first->now_size++;
            total_num++;
        }
    }
    void pop_front() {
        if(total_num==0)throw("the_container_is_empty");
        total_num--;
        first->now_size--;
        delete first->p[0];
        for(int i=0;i<first->now_size;i++){
            first->p[i]=nullptr;
            first->p[i]=first->p[i+1];
        }
        first->p[first->now_size]=nullptr;
        if(first->next!=nullptr){
            if(first->now_size+(first->next)->now_size<=n){
                    first=merge(first,first->next);
            }
        }
    }
};
}
#endif
