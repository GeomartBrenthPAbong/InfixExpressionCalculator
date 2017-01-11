#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H

namespace gba
{

    template<typename T>
    class QueueNode
    {
        public:
            QueueNode();
            QueueNode(T p_data);
            ~QueueNode();

            void setData(T p_data);
            void setNextNode(QueueNode<T> *p_node);

            T getData();
            QueueNode<T> *getNextNode();

        private:
            QueueNode *m_next_node;
            T m_data;
    };

}

#include "QueueNode.cpp"

#endif