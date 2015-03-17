#ifndef NODE_H
#define NODE_H

class Node{
    private:
        static const int size = 50;    // 50 nodes
        bool vis;                    // True/False if node has been visited
        int connected [size];          // Connected nodes
        int count;                   // Keep track of the connected index

    public:
    // constructor for our node
        Node (){
            count = 0;
            vis=false;
        }

    // connects a node to the current node
        void connect(int node){
            connected[count] = node;
        }
    
    // Returns vis
        bool getVis(){
            return vis;
        }
    // Swaps the vis truth value
        void swapBoolean(){
            vis=!vis;
        }

    // Checks if node is connected to anything
        bool isConnected(){
            return (count != 0);
        }

    // Return count
        int getCount(){
            return count;
        }


    // Call getConnected() and return the next node
        int getConnected(){
            return connected[count];
        }

    // Increment count by 1
        void nextcount(){
            count++;
        }

    // Sets the count to a given int x
        void setcount(int x){
            count = x;
        }

    // Decrements count by 1
        void previouscount(){
            count--;
        }

    // Inputs val into the connected[]
        void inputConnected(int val){
            connected[count]=val;
        }
};

#endif
