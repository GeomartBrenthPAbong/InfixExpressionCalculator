template<typename T>
gba::LinkedListQueue<T>::LinkedListQueue():
    m_root(0), m_runner_node(0), m_size(0){}

template<typename T>
gba::LinkedListQueue<T>::~LinkedListQueue()
{
    QueueNode<T> *temp_node;
    m_runner_node = m_root;
    
    while(0 != m_runner_node)
    {
        temp_node = m_runner_node->getNextNode();
        delete m_runner_node;
        m_runner_node = temp_node;
    }

    m_root = 0;
    temp_node = 0;
}

template<typename T>
void gba::LinkedListQueue<T>::enqueue(T p_data)
{
    m_size++;

    if(0 == m_root)
    {
        m_root = new QueueNode<T>(p_data);
        m_runner_node = m_root;
    }
    else
    {
        m_runner_node->setNextNode(new QueueNode<T>(p_data));
        m_runner_node = m_runner_node->getNextNode();
    }
}

template<typename T>
T gba::LinkedListQueue<T>::dequeue()
{
    if(isEmpty())
        return 0;

    --m_size;
    T data = m_root->getData();

    QueueNode<T> *old_root = m_root;
    m_root = m_root->getNextNode();

    delete old_root;
    old_root = 0;

    return data;
}

template<typename T>
T gba::LinkedListQueue<T>::front()
{
    if(isEmpty())
        return 0;

    return m_root->getData();
}

template<typename T>
bool gba::LinkedListQueue<T>::isEmpty()
{
    return 0 == m_size;
}

template<typename T>
int gba::LinkedListQueue<T>::size()
{
    return m_size;
}