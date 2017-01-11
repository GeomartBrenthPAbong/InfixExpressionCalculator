#ifndef QUEUE_H
#define QUEUE_H

namespace gba
{

    template<typename T>
    class Queue
    {
        public:
            virtual ~Queue(){};

            virtual void enqueue(T p_data) = 0;
            virtual T dequeue() = 0;
            virtual T front() = 0;
            virtual bool isEmpty() = 0;
            virtual int size() = 0;
    };

}

#endif