#ifndef YAGL_NODE_H
#define YAGL_NODE_H

#pragma once 

#include <iostream>
#include <fstream>
// #include "proto/node.pb.h"

namespace YAGL
{
    template <typename KeyType, typename DataType>
    class Node;

    template <typename KeyType, typename DataType>
    std::ostream& operator<<(std::ostream& os, const Node<KeyType, DataType>& node);

    template <typename KeyType, typename DataType>
    class Node
    {
        public:
            using data_type = DataType;
            using key_type = KeyType;
            
            Node(const KeyType, const DataType& data);
            ~Node() = default;

            const KeyType& getKey() const;
            DataType& getData();

            bool operator==(const Node<KeyType, DataType>& b) const;
            bool operator<(const Node<KeyType, DataType>& b) const;

            friend std::ostream &operator<<<>(std::ostream &os, const Node<KeyType, DataType>& node);

        private:
            KeyType key;
            DataType data;  
    };

    template <typename KeyType, typename DataType>
    Node<KeyType, DataType>::Node(const KeyType k, const DataType& d)
    : key(k), data(d) //TODO: possibly make it a move
    {
    }

    template <typename KeyType, typename DataType>
    const KeyType& Node<KeyType, DataType>::getKey() const
    {
        return key;
    }

    template <typename KeyType, typename DataType>
    DataType& Node<KeyType, DataType>::getData() 
    {
        return data;
    }

    template <typename KeyType, typename DataType>
    bool Node<KeyType, DataType>::operator==(const Node<KeyType, DataType>& b) const
    {
        return (this->key == b.key && this-> data == b.data);
    }
    
    template <typename KeyType, typename DataType>
    std::ostream &operator<<(std::ostream &os, const Node<KeyType, DataType>& node)
    {
        os << "Node: {\n"
             << "\tKey:\t" << node.key << "\n"
             << "\tData:\t" << node.data << "\n"
             << "}\n";
        return os;
    }

    /*
    template <typename KeyType, typename DataType>
    void to_proto(Node<KeyType, DataType>& node, std::string &output)
    {
        yagl::Node proto_node;

        std::string str_key = std::to_string(node.getKey());
        std::string str_data = std::to_string(node.getData());

        proto_node.set_key(str_key);
        proto_node.set_data(str_data);

        // serialize
        if(!proto_node.SerializeToString(&output))
        {
            throw std::runtime_error("Failed to write node to output stream.");
        }

        std::cout << "Serialized Node to proto string.\n";
        // print it out
        std::cout << proto_node.DebugString() << "\n";

        // Save to file:
        std::ofstream out("node.bin", std::ios::binary);
        out.write(output.data(), output.size());
    }
    */

} //end namespace YAGL

#endif
