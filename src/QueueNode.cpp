template<typename T>
gba::QueueNode<T>::QueueNode():
    m_next_node(0){}

template<typename T>
gba::QueueNode<T>::QueueNode(T p_data):
    m_next_node(0), m_data(p_data){}

template<typename T>
gba::QueueNode<T>::~QueueNode()
{
    m_next_node = 0;
}

template<typename T>
void gba::QueueNode<T>::setData(T p_data)
{
    m_data = p_data;
}

template<typename T>
void gba::QueueNode<T>::setNextNode(gba::QueueNode<T> *p_node)
{
    m_next_node = p_node;
}

template<typename T>
T gba::QueueNode<T>::getData()
{
    return m_data;
}

template<typename T>
gba::QueueNode<T> *gba::QueueNode<T>::getNextNode()
{
    return m_next_node;
}