// Simple definition of a class implementing Sendable and Receivable interfaces.
// This allows instances to be passed directly to socket send/receive methods.

#include <CpperoMQ/All.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

template <typename T>
CpperoMQ::OutgoingMessage serializeNumber(const T number)
{
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type.");

    std::ostringstream strStream;
    strStream << number;

    CpperoMQ::OutgoingMessage msg(strStream.str().c_str());
    return msg;
}

template <typename T = int>
T deserializeNumber(const CpperoMQ::IncomingMessage& msg)
{
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type.");

    T number = T();

    std::istringstream strStream(std::string(msg.charData(), msg.size()));
    strStream >> number;

    return number;
}

class Employee : public CpperoMQ::Sendable
               , public CpperoMQ::Receivable
{
public:
    Employee()
        : mId(0)
        , mAge(0)
        , mName("Unknown")
    {
    }

    Employee(int id, int age, std::string name)
        : mId(id)
        , mAge(age)
        , mName(name)
    {
    }

    virtual bool send(const CpperoMQ::Socket& socket, const bool moreToSend) const override
    {
        using namespace CpperoMQ;

        OutgoingMessage idMsgPart(serializeNumber(mId));
        if (!idMsgPart.send(socket, true))
            return false;

        OutgoingMessage ageMsgPart(serializeNumber(mAge));
        if (!ageMsgPart.send(socket, true))
            return false;

        OutgoingMessage nameMsgPart(mName.c_str());
        if (!nameMsgPart.send(socket, moreToSend))
            return false;

        return true;
    }

    virtual bool receive(CpperoMQ::Socket& socket, bool& moreToReceive) override
    {
        using namespace CpperoMQ;

        IncomingMessage idMsgPart;
        if (!idMsgPart.receive(socket, moreToReceive) || !moreToReceive)
            return false;

        IncomingMessage ageMsgPart;
        if (!ageMsgPart.receive(socket, moreToReceive) || !moreToReceive)
            return false;

        IncomingMessage nameMsgPart;
        if (!nameMsgPart.receive(socket, moreToReceive))
            return false;

        mId  = deserializeNumber(idMsgPart);
        mAge = deserializeNumber(ageMsgPart);

        mName.assign(nameMsgPart.charData(), nameMsgPart.size());

        return true;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Employee& e)
    {
        stream << e.mId << "," << e.mAge << "," << e.mName;
        return stream;
    }

private:
    int mId;
    int mAge;
    std::string mName;
};

class Department : public CpperoMQ::Sendable
                 , public CpperoMQ::Receivable
{
public:
    Department()
        : mCode(0)
        , mName("Unknown")
    {
    }

    Department(int id, std::string name)
        : mCode(id)
        , mName(name)
    {
    }

    virtual bool send(const CpperoMQ::Socket& socket, const bool moreToSend) const override
    {
        using namespace CpperoMQ;

        OutgoingMessage idMsgPart(serializeNumber(mCode));
        if (!idMsgPart.send(socket, true))
            return false;

        OutgoingMessage nameMsgPart(mName.c_str());
        if (!nameMsgPart.send(socket, moreToSend))
            return false;

        return true;
    }

    virtual bool receive(CpperoMQ::Socket& socket, bool& moreToReceive) override
    {
        using namespace CpperoMQ;

        IncomingMessage idMsgPart;
        if (!idMsgPart.receive(socket, moreToReceive) || !moreToReceive)
            return false;

        IncomingMessage nameMsgPart;
        if (!nameMsgPart.receive(socket, moreToReceive))
            return false;

        mCode = deserializeNumber(idMsgPart);
        mName.assign(nameMsgPart.charData(), nameMsgPart.size());

        return true;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Department& d)
    {
        stream << d.mCode << ","  << d.mName;
        return stream;
    }

private:
    int mCode;
    std::string mName;
};

class DepartmentUpdate : public CpperoMQ::Sendable
                       , public CpperoMQ::Receivable
{
public:
    DepartmentUpdate()
        : mOldDept()
        , mNewDept()
        , mEmployee()
    {
    }

    DepartmentUpdate( const Department& oldDept
                    , const Department& newDept
                    , const Employee& employee )
        : mOldDept(oldDept)
        , mNewDept(newDept)
        , mEmployee(employee)
    {
    }

    virtual bool send(const CpperoMQ::Socket& socket, const bool moreToSend) const override
    {
        using namespace CpperoMQ;

        if (!mOldDept.send(socket, true))
            return false;

        if (!mNewDept.send(socket, true))
            return false;

        if (!mEmployee.send(socket, moreToSend))
            return false;

        return true;
    }

    virtual bool receive(CpperoMQ::Socket& socket, bool& moreToReceive) override
    {
        using namespace CpperoMQ;

        if (!mOldDept.receive(socket, moreToReceive) || !moreToReceive)
            return false;

        if (!mNewDept.receive(socket, moreToReceive) || !moreToReceive)
            return false;

        if (!mEmployee.receive(socket, moreToReceive))
            return false;

        return true;
    }

    friend std::ostream& operator<<(std::ostream& stream, const DepartmentUpdate& du)
    {
        stream << du.mOldDept << "|"  << du.mNewDept << "|" << du.mEmployee;
        return stream;
    }

private:
    Department mOldDept;
    Department mNewDept;
    Employee mEmployee;
};
