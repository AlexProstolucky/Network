#include <iostream>
#include <string>
#include <vector> 

using namespace std;

class IP
{
public:
    uint8_t address[4];
    uint8_t mask[4];
    string Class;
public:
    IP()
    {
        address[0] = 0;
        address[1] = 0;
        address[2] = 0;
        address[3] = 0;

        mask[0] = 0;
        mask[1] = 0;
        mask[2] = 0;
        mask[3] = 0;
    }

    void print()
    {
        string str;
        string _mask;
        for (size_t i = 0; i < 3; i++)
        {
            str += to_string(address[i]) + '.';
            _mask += to_string(mask[i]) + '.';
        }
        str += to_string(address[3]);
        _mask += to_string(mask[3]);
        cout << "IP: " << str << " Mask: " << _mask << " Class: " << Class << endl;
    }
    void classinfo()
    {
        int num = address[0];
        if (num >= 0 && 127 >= num) { Class = "A"; }

        else if (num >= 128 && 191 >= num) { Class = "B"; }

        else if (num >= 192 && 223 >= num) { Class = "C"; }

        else if (num >= 224 && 239 >= num) { Class = "D"; }

        else { Class = "E"; }
    }

    void parse( string& saddress)
    {
        size_t last_pos = 0;
        size_t pos = 0;
        size_t i = 0;
        saddress += ".";
        while (saddress.find('.', pos + 1) != saddress.npos && i < 4)
        {
            pos = saddress.find('.', pos + 1);
            address[i] = stoi(saddress.substr(last_pos, pos - last_pos));
            last_pos = pos + 1;
            i++;
        }

        classinfo();
        if (Class == "A") mask[0] = 255;
        else if (Class == "B") {
            mask[0] = 255;
            mask[1] = 255;
        }
        else if (Class == "C") {
            mask[0] = 255;
            mask[1] = 255;
            mask[2] = 255;
        }
        else {
            mask[0] = 255;
            mask[1] = 255;
            mask[2] = 255;
            mask[3] = 255;
        }
    }

    IP(string ip) :IP()
    {
        parse(ip);
        cout << "IP created:" << endl;
        print();
    }
};

class Network : public IP
{
private:
    vector <IP> network;
public:
    Network(string address) :IP(address)
    {
        cout << endl;
        cout << "Main IP set:" << endl;
        print();
    }

    void add(IP _ip)
    {
        if (_ip.address[0] == 192 || _ip.address[0] == 168) {
            network.push_back(_ip);
            cout << endl;
            _ip.print();
            cout << "Added to network!" << endl;
        }
        else {
            cout << "Error in input IP!" << endl;
            cout << "IP must have 192... or 168..." << endl;
        }
    }

    void remove(IP _ip) {
        if (!network.empty())
        {
            int buff = _ip.address[4];
            IP ip_buff;
            cout << endl;
            for (size_t i = 0; i < network.size(); i++)
            {
                ip_buff = network[i];
                if (ip_buff.address[4] == buff)
                {
                    network.erase(network.begin() + i);
                    cout << "IP address removed:" << endl;
                    _ip.print();
                    return;
                }
            }
            cout << "IP address didn`t remove, Error input!" << endl;
        }
        else cout << "Network is emtpy!" << endl;
    }


    void info() 
    {
        if (!network.empty())
        {
            cout << endl;
            cout << "INFO OF NETWORK:" << endl;
            for (size_t i = 0; i < network.size(); i++)
            {
                IP buff = network[i];
                buff.print();
            }
        }
        else cout << "Network is empty!" << endl;
    }
};

int main()
{
    IP ip1("192.168.0.1");
    IP ip2("192.168.0.2");
    IP ip3("192.168.0.3");
    Network network_192("192.168.0.0");
    Network network_168("168.254.0.0");
    network_192.add(ip1);
    network_192.add(ip2);
    network_192.add(ip3);
    network_192.info();
    network_192.remove(ip1);
    network_192.remove(ip2);
    network_192.remove(ip3);
    network_192.info();
    IP ip4("168.254.0.1");
    IP ip5("168.254.0.2");
    IP ip6("168.254.0.3");
    network_168.add(ip4);
    network_168.add(ip5);
    network_168.add(ip6);
    network_168.info();
    network_168.remove(ip4);
    network_168.remove(ip5);
    network_168.remove(ip6);
    network_168.info();
}