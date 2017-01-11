#ifndef LINKEDLIST_QUEUE_H
#define LINKEDLIST_QUEUE_H

#include "QueueNode.hpp"
#include "Queue.hpp"

namespace gba
{

    template<typename T>
    class LinkedListQueue: public Queue<T>
    {
        public:
            LinkedListQueue();
            ~LinkedListQueue();

            void enqueue(T p_data);
            T dequeue();
            T front();
            bool isEmpty();
            int size();

        private:
            QueueNode<T> *m_root;
            QueueNode<T> *m_runner_node;
            int m_size;
    };

}

#include "LinkedListQueue.cpp"

#endif