
#include "set.h"

void print( std::ostream& out, const treenode* n, size_t indent )
{

   for( size_t i = 0; i != indent; ++ i )
      out << "|  "; 
   if(n)
   {
      out << ( n -> val ) << "\n";
      print( out, n -> left, indent + 1 );
      print( out, n -> right, indent + 1 ); 
   }
   else
      out << "#\n"; 
}


// both the upperbound and the lowerbound are strict,
// we use pointers, so that they can be absent. 

void checkbetween( const treenode* n, 
                   const int* lowerbound, const int* upperbound ) 
{
   while(n) 
   {
      if( lowerbound && *lowerbound >= n -> val )
      {
         std::cout << "value " << ( n -> val );
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         std::abort( );
      }

      if( upperbound && n -> val >= *upperbound )
      {
         std::cout << "value " << ( n -> val );
         std::cout << "is not below upperbound " << *upperbound << "\n";
         std::abort( );
      }

      checkbetween( n -> left, lowerbound, &( n -> val ));
      lowerbound = & ( n -> val );
      n = n -> right;
   }
} 


void deallocate( treenode* n )
{
   while(n)
   {
      deallocate( n -> left );
      treenode* bye = n;
      n = n -> right;
      delete bye;
   }
}


void writecopy( treenode** to, treenode* from )
{
   while( from )
   {
      *to = new treenode{ from -> val };

      writecopy( & (*to) -> left, from -> left );
      to = & (*to) -> right;
      from = from -> right;
   }
}


void set::checksorted( ) const
{
   ::checkbetween( tr, nullptr, nullptr );
}


std::ostream& set::print( size_t indent, std::ostream& out ) const
{
   ::print( out, tr, indent );
   return out;
}

const treenode* find(const treenode* n, int i){
    if (n==nullptr){
        return n;
    }
    else if (n->val==i){
        return n;
    }
    else if (n->val<i){
        return find(n->right, i);
    }
    else {
        return find(n->left, i);
    }
}

treenode** find(treenode** n, int i){
    if (*n==nullptr){
           return n;
       }
    else if ((*n)->val==i){
        return n;
    }
    else if ((*n)->val>i){
        if ((*n)->left==nullptr){
            return n;
        }
        else {
            n=&((*n)->left);
            return find(n, i);
        }
    }
    else {
        if ((*n)->right==nullptr){
            return n;
        }
        else {
            n=&((*n)->right);
            return find(n, i);
        }
    }
}



treenode* removerightmost( treenode** from ){
    treenode *a;
    a=((*from)->left);
    while(a->right!=nullptr){
        a=a->right;
    }
    return a;
}

size_t height( const treenode* n ){
    if (n==nullptr){
        return 0;
    }
    size_t left=height(n->left);
    size_t right=height(n->right);
    return 1+max(left, right);
}

size_t max(size_t a, size_t b){
    if (a>b){
        return a;
    }
    else return b;
}

size_t size( const treenode* n ){
    if (n==nullptr){
        return 0;
    }
    else
        return(size(n->left) + 1 + size(n->right));
}

size_t log_base2( size_t s ){
    size_t a=1;
    size_t n=0;
    if(s==0){
        return 0;
    }
    while(s>=a){
        ++n;
        a=2*a;
    }
    return n-1;
}

bool set::insert(int i){
   if (tr==nullptr){
       tr=new treenode(i);
       return true;
   }
    treenode **parent_node;
    parent_node=find(&tr, i);
   if ((*parent_node)->val==i){
       return false;
   }
   else {
       if ((*parent_node)->val>i){
           (*parent_node)->left=new treenode(i);
       }
       else {
           (*parent_node)->right=new treenode(i);
       }
   }
   return true;
}


bool set::remove( int i ){
        treenode **node;
        node=&tr;
        treenode **parent_node;
        parent_node=find(node, i);
        if ((*parent_node)->val!=i){
            return false;
        }
        else if ((((*parent_node)->left)==nullptr)&&((*parent_node)->right==nullptr)){
            delete(*parent_node);
            *parent_node=nullptr;
        }
        else if ((((*parent_node)->left)!=nullptr)&&((*parent_node)->right==nullptr)){
            treenode *remove_node;
            remove_node=(*parent_node);
            (*parent_node)=(*parent_node)->left;
            delete(remove_node);
            remove_node=nullptr;
        }
        else if (((*parent_node)->left==nullptr)&&(((*parent_node)->right)!=nullptr)){
            treenode *remove_node;
            remove_node=(*parent_node);
            (*parent_node)=(*parent_node)->right;
            delete(remove_node);
            remove_node=nullptr;
        }
        else {
            treenode *delete_node;
            treenode **remove_node;
            delete_node=removerightmost(find(&tr, i));
            int max=delete_node->val;
            remove_node=find(&tr, max);
            (*find(&tr, i))->val=(max);
            if (delete_node->left==nullptr){
                delete(*remove_node);
                *remove_node=nullptr;
            }
            else {
                (*remove_node)=(*remove_node)->left;
                delete(delete_node);
                delete_node=nullptr;
            }
        }
        return true;
}

bool set::contains( int i ) const {
        if (find(tr, i)!=nullptr){
            return true;
        }
        else return false;
}

void set::clear( ){
        if (tr==nullptr){
            return;
        }
       while(tr!=nullptr){
           treenode *a;
           a=tr;
           tr=tr->left;
           clear();
           tr=a->right;
           clear();
       }
       return;
}

bool set::isempty( ){
        if (tr==nullptr) return true;
        else return false;
}
