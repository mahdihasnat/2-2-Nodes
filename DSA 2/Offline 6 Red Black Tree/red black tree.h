#ifndef RED_BLACK_TREE_ADDED
#define RED_BLACK_TREE_ADDED


#define RED  0
#define BLACK 1

template<class T >
class RBT ;

template < class T >
class  Node
{
private :
    T value;
    Node * left, * right, * parent;
    bool color ;

    void rotate(Node<T> * child)
    {
        child->parent = parent;

        if(parent)
        {
            if(parent->left == this)
                parent ->left = child;
            else
                parent->right = child;
        }

        if(child == left )
        {

            left = child->right ;
            if(child->right)
                child->right ->parent = this;

            child->right = this;
            parent = child;

        }
        else
        {

            right = child->left ;
            if(child->left)
                child->left ->parent = this;

            child->left = this;
            parent = child;
        }
    }



    int check_RBT()
    {
        int x=  0;
        if(left)
        {
            if(color == RED)
                assert(left->color == BLACK);
            x= left->check_RBT();
        }
        if(right)
        {
            if(color == RED)
                assert(right->color == BLACK);
            assert(x == right->check_RBT());
        }
        else
            assert(x==0);
        if(color == BLACK)
            x++;
        return x;
    }


public :
    Node(T value, bool color):value(value), left(0), right(0), parent(0), color(color) {}

    void pre_order()
    {
        cout<<value<<":"<<(color == RED ? 'r' :'b');
        if(left or right)
        {
            cout<<"(";
            if(left)
                left->pre_order();
            cout<<")(";
            if(right)
                right->pre_order();
            cout<<")";
        }
    }

    friend class RBT < T> ;

};

#define CheckRED(x) ((x) and (x)->color == RED )
#define CheckBLACK(x) ((x) ==0  or (x)->color == BLACK )
template<class T >
class RBT
{
private :
    Node<T> * root  ;

    void insert_fixup(Node < T > * z)
    {
        while(z->parent != 0 and z->parent->color == RED)
        {
            assert(z->parent->parent);
            Node<T > * y = 0;
            if(z->parent->parent)
                y = z->parent == z->parent->parent->left ? z->parent->parent->right : z->parent->parent->left;
            if(y != 0 and y->color == RED) /// case 1 uncle y is red
            {
                y->color = BLACK ;
                z->parent->color = BLACK ;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if( (z == z->parent ->left ) ^ (z->parent == z->parent->parent ->left) ) /// case 2 , asymmetric uncle black
                {
                    Node<T> * tmp = z->parent ;
                    z->parent->rotate(z);
                    z= tmp;
                }
                assert( ((z == z->parent ->left ) ^ (z->parent == z->parent->parent ->left)) == 0);

                /// case 3 asymmetric
                Node<T> * old_grand_parent = z->parent->parent;
                Node<T> * old_parent = z->parent;
                z->parent->parent->rotate(z->parent);

                z->parent->color = BLACK ;
                old_grand_parent ->color = RED;
                if(old_parent->parent == 0 )
                    root = old_parent;
            }
        }

        root->color = BLACK;
    }


    void delete_fixup(Node<T> * x, Node < T > * px)
    {
        while(x != root and (x == 0 or x->color == BLACK) )
        {
            assert(px);
            Node<T> * w = px->left == x ? px->right : px->left ;
            assert(w);

            if( w->color == RED) /// case 1
            {
                swap(w->color, px->color);
                px->rotate(w);

                if( w->parent == 0)
                    root = w;
            }
            else if((w->left==0 or  w->left->color == BLACK) and (w->right ==0 or w->right->color == BLACK) ) /// case 2
            {
                w->color = RED ;
                x = px;
                px = x->parent;
            }
            else
            {
                if(px->left == x and CheckRED(w->left) and CheckBLACK(w->right) ) /// case 3
                {
                    w->rotate(w->left);
                    w->color = RED;
                    w->parent->color = BLACK;
                    w=w->parent;
                }
                if(px->right == x and CheckRED(w->right) and CheckBLACK(w->left) ) /// case 3
                {
                    w->rotate(w->right);
                    w->color = RED;
                    w->parent->color = BLACK;
                    w=w->parent;
                }

                /// case 4
                if(px->left == x)
                {
                    assert(CheckRED(w->right));
                    w->color = px->color ;
                    px->color = w->right->color = BLACK;
                    px->rotate(w);
                    if(w->parent ==0 )
                        root = w;
                    x=root;
                }
                else
                {
                    assert(CheckRED(w->left));
                    w->color = px->color ;
                    px->color = w->left->color = BLACK;
                    px->rotate(w);
                    if(w->parent ==0 )
                        root = w;
                    x=root;
                }

            }

        }
        if(x)
            x->color = BLACK ;
    }

    void validate_RBT()
    {
        if(root)
        {
            assert(root->color == BLACK);
            root->check_RBT();
        }
    }

public :
    RBT() : root(0) { }
    void insert(T value)
    {
        Node<T> * z = new Node<T> (value, RED);
        Node<T> * x = root;
        Node<T> * y = 0;
        while(x)
        {
            y = x;
            if(z->value < x->value)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if ( y == 0)
            root = z;
        else if(z->value < y->value)
            y->left = z;
        else
            y->right = z;

        insert_fixup(z);
        //validate_RBT();

    }
    bool find(T value)
    {
        Node<T> * x = root;
        while(x )
        {
            if(x->value < value)
                x = x->right;
            else if(x->value == value)
                return 1;
            else
                x = x->left;
        }
        return 0;
    }

    bool Delete(T value)
    {
        Node<T> * z = root;

        while(z)
        {
            if(z->value < value)
                z=z->right;
            else if(z->value == value )
                break;
            else
                z = z->left;
        }
        if(z == 0)
            return 0;

        Node<T> * y  = z;
        if(z->left and z->right)
        {
            y=z->right;
            while(y->left)
                y=y->left;
        }



        Node<T> * x = y->left ? y->left : y->right;

        swap(z->value, y->value);

        if(x)
            x->parent = y->parent;
        if(y->parent)
        {
            if(y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
        }
        else
        {
            root = x;
        }

        assert(y);
        if(y->color == BLACK)
            delete_fixup(x, y->parent );

        delete y;

        //validate_RBT();
        return 1;
    }
    void print()
    {
        if(root)
            root->pre_order();
    }
};

#endif // RED_BLACK_TREE_ADDED
