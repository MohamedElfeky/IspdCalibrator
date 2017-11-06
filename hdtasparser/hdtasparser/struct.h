﻿//
// Created by wanghaiyang on 12/23/16.
//

#ifndef HDTAS_STRUCT_H
#define HDTAS_STRUCT_H

#include "header.h"
#include <string.h>
#ifdef HDTAS_WINDOWS
#include <Winsock2.h>
#endif
namespace hdtas
{
    /**
     * @brief Location algorithm version.
     */
    enum loca_algo_vers
    {
        la_version_1 = 1,
        la_version_2 = 2 // Algorithm from System software department.
    };

    typedef struct redis_mq_info
    {
        std::string user;
        std::string host;
        std::string password;
        std::string pub_channel;
        std::string sub_channel;
        int port;
        bool pub_or_sub; // True: publish message, False: subscribe message.

        redis_mq_info() :
                port(0),
                pub_or_sub(true)
        {}
    } redis_mq_info;

    typedef struct database_info
    {
        unsigned int port;
        std::string host;
        std::string user;
        std::string password;
        std::string dbname;

        database_info() :
            port(0)
        {}
    } database_info;

    /**
     * @brief
     */
    typedef struct ispd_date_time
    {
        h_uint16 y;
        h_uint16 m;
        h_uint16 d;
        h_uint16 h;
        h_uint16 n;
        h_uint16 s;
        h_uint16 ms; /** Milliseconds */

        ispd_date_time() :
            y(0), m(0), d(0), h(0), n(0), s(0), ms(0)
        {
        }
#ifdef HDTAS_WINDOWS
        ispd_date_time( const SYSTEMTIME& v )
        {
            y = v.wYear;
            m = v.wMonth;
            d = v.wDay;
            h = v.wHour;
            n = v.wMinute;
            s = v.wSecond;
            ms = v.wMilliseconds;
        }
#else
        ispd_date_time( const struct timeval& v )
        {
            struct tm* lt = localtime( &v.tv_sec );
            y = lt->tm_year;
            m = lt->tm_mon;
            d = lt->tm_mday;
            h = lt->tm_hour;
            n = lt->tm_min;
            s = lt->tm_sec;
            ms = v.tv_usec / 1000; // usec: Microsecond.
        }
#endif

    } ispd_date_time;

    enum mr_update_type {
        MUT_SOFT = 0
    };

    typedef struct mr_update_info {
        char name[LEN_MAX_MR_UPDATE_FILE_NAME+1];
        mr_update_type type;
        h_uint32 length;
        h_uint32 hash;
        std::string version;

        mr_update_info() :
            type(mr_update_type::MUT_SOFT), length(0), hash(0)
        {
            memset( name, 0, LEN_MAX_MR_UPDATE_FILE_NAME+1 );
        }

        mr_update_info( const char* n, mr_update_type t, h_uint32 l, h_uint32 h )
        {
            STRNCPY( name, LEN_MAX_MR_UPDATE_FILE_NAME, n, STRLEN(n) );
            type = t;
            length = l;
            hash = h;
        }

        mr_update_info( const mr_update_info& info )
        {
            STRNCPY( this->name, LEN_MAX_MR_UPDATE_FILE_NAME, info.name, STRLEN(info.name) );
            this->type = info.type;
            this->length = info.length;
            this->hash = info.hash;
            this->version = info.version;
        }

        mr_update_info& operator = ( const mr_update_info& info )
        {
            STRNCPY( this->name, LEN_MAX_MR_UPDATE_FILE_NAME, info.name, STRLEN(info.name) );
            this->type = info.type;
            this->length = info.length;
            this->hash = info.hash;
            this->version = info.version;
            return *this;
        }
    } mr_update_info;

    typedef struct mr_info {
        union_id uid;
        device_mr_id mrid;
        std::string mrid2;

        mr_info() :
            uid(0), mrid(0)
        {}

        void reset()
        {
            uid = 0;
            mrid = 0;
            mrid2.clear();
        }
    } mr_info;

    typedef struct mr_info_ext {
        mr_info info;
        point_3d<double> position;

        void reset()
        {
            this->info.reset();
            position.x = 0.0;
            position.y = 0.0;
            position.z = 0.0;
        }
    } mr_info_ext;

    typedef std::map<device_mr_id, mr_info_ext> mr_info_ext_container;
    typedef mr_info_ext_container::iterator mr_info_ext_container_it;
    typedef mr_info_ext_container::const_iterator mr_info_ext_container_cit;

    typedef std::map<union_id, mr_info> u_mr_info_container;
    typedef u_mr_info_container::iterator u_mr_info_container_it;
    typedef u_mr_info_container::const_iterator u_mr_info_container_cit;

    typedef struct mr_config_info
    {
        h_uint32 stu;
        char ip[LEN_MAX_IP_ADDRESS]; // Mmr local ip address.
        char nm[LEN_MAX_IP_ADDRESS]; // Netmask address.
        char gw[LEN_MAX_IP_ADDRESS]; // Gateway address.
        char dns[LEN_MAX_IP_ADDRESS]; // DNS address.
        char mac[LEN_MAX_MAC_ADDRESS]; // Mac address.
        char tip[LEN_MAX_IP_ADDRESS]; // Tcp server address.
        char uip[LEN_MAX_IP_ADDRESS]; // Udp server address.
        h_uint32 tport; // Tcp server port.
        h_uint32 uport; // Udp server port.

        mr_config_info() :
            stu(0), tport(0), uport(0)
        {}

        mr_config_info(const mr_config_info& info)
        {
            this->stu = info.stu;
            STRNCPY(this->ip, LEN_MAX_IP_ADDRESS, info.ip, strlen(info.ip));
            STRNCPY(this->nm, LEN_MAX_IP_ADDRESS, info.nm, strlen(info.nm));
            STRNCPY(this->gw, LEN_MAX_IP_ADDRESS, info.gw, strlen(info.gw));
            STRNCPY(this->dns, LEN_MAX_IP_ADDRESS, info.dns, strlen(info.dns));
            STRNCPY(this->mac, LEN_MAX_MAC_ADDRESS, info.mac, strlen(info.mac));
            STRNCPY(this->tip, LEN_MAX_IP_ADDRESS, info.tip, strlen(info.tip));
            STRNCPY(this->uip, LEN_MAX_IP_ADDRESS, info.uip, strlen(info.uip));
            this->tport = info.tport;
            this->uport = info.uport;

        }

        mr_config_info& operator = (const mr_config_info& info)
        {
            this->stu = info.stu;
            STRNCPY(this->ip, LEN_MAX_IP_ADDRESS, info.ip, strlen(info.ip));
            STRNCPY(this->nm, LEN_MAX_IP_ADDRESS, info.nm, strlen(info.nm));
            STRNCPY(this->gw, LEN_MAX_IP_ADDRESS, info.gw, strlen(info.gw));
            STRNCPY(this->dns, LEN_MAX_IP_ADDRESS, info.dns, strlen(info.dns));
            STRNCPY(this->mac, LEN_MAX_MAC_ADDRESS, info.mac, strlen(info.mac));
            STRNCPY(this->tip, LEN_MAX_IP_ADDRESS, info.tip, strlen(info.tip));
            STRNCPY(this->uip, LEN_MAX_IP_ADDRESS, info.uip, strlen(info.uip));
            this->tport = info.tport;
            this->uport = info.uport;

            return *this;
        }
    } mr_config_info;

    typedef struct mr_config_info2
    {
        h_uint32 stu;
        h_uint32 ip; // Mmr local ip address.
        h_uint32 nm; // Netmask address.
        h_uint32 gw; // Gateway address.
        h_uint32 dns; // DNS address.
        h_uint8 mac[6]; // Mac address.
        h_uint32 tip; // Tcp server address.
        h_uint32 tport; // Tcp server port.
        h_uint32 uip; // Udp server address.
        h_uint32 uport; // Udp server port.

        mr_config_info2() :
            stu(0), ip(0), nm(0), gw(0), dns(0),
            tip(0), tport(0), uip(0), uport(0)
        {
            memset( mac, 6, 0 );
        }

        mr_config_info2(const mr_config_info2& info)
        {
            this->stu = info.stu;
            this->ip = info.ip;
            this->nm = info.nm;
            this->gw = info.gw;
            this->dns = info.dns;
            memcpy(this->mac, info.mac, 6);
            this->tip = info.tip;
            this->tport = info.tport;
            this->uip = info.uip;
            this->uport = info.uport;
        }

        mr_config_info2& operator = (const mr_config_info2& info)
        {
            this->stu = info.stu;
            this->ip = info.ip;
            this->nm = info.nm;
            this->gw = info.gw;
            this->dns = info.dns;
            memcpy(this->mac, info.mac, 6);
            this->tip = info.tip;
            this->tport = info.tport;
            this->uip = info.uip;
            this->uport = info.uport;
            return *this;
        }
    } mr_config_info2;

    typedef struct mr_time_diff
    {
        device_mr_id id;
        h_uint32 td;

        mr_time_diff() :
            id(0), td(0)
        {
        }

        mr_time_diff( device_mr_id i, h_uint32 t ) :
                id(i),
                td(t)
        { }
    } mr_time_diff;

    typedef std::vector<mr_time_diff> mr_time_diff_array;

    typedef struct ispd_data_stu
    {
        ispd_id id;
        mr_time_diff_array tds;

        point_3d<h_int16> acceleration;
        point_3d<h_int16> gyroscope;

        h_uint32 heart_rate;
        h_uint32 power;
        h_uint32 charge;

        bool isContainSensor;

        ispd_data_stu() : id(0), heart_rate(0), power(0), charge(0)
        {}
    } ispd_data_stu;

    typedef std::vector<ispd_data_stu> isdp_data_array;

    typedef struct mr_status_stu
    {
        device_mr_id id;
        h_uint16 status; // 0: online, other: offline

        mr_status_stu() :
            id(0), status(0)
        { }

        mr_status_stu( device_mr_id i, h_uint16 s ) :
                id(i),
                status(s)
        { }
    } mr_status_stu;

    typedef std::vector<mr_status_stu> mr_status_array;

    typedef struct mr_status2_t
    {
        union_id id;
        h_uint16 status;

        mr_status2_t() :
            id(0), status(0)
        {}
    } mr_status2;

    typedef std::vector<mr_status2> mr_status_array2;

    typedef struct mr_status3_t
    {
        union_id uid;
        device_mr_id mrid;
        std::string mrid2;
        h_uint16  status;

        mr_status3_t() :
            uid(0), mrid(0), status(0)
        {}
    } mr_status3;

    typedef std::vector<mr_status3> mr_status_array3;

    typedef struct mr_configure
    {
        h_uint16 status;
        h_uint32 s_ip;
        h_uint32 s_netmask;
        h_uint32 s_gateway;
        h_uint32 s_dns;

        h_uint32 d_ip;
        h_uint32 d_netmask;
        h_uint32 d_gateway;
        h_uint32 d_dns;

        char macaddr[LEN_MAX_MACADDR_STRING+1];
        char domain[LEN_MAX_DOMAIN_STRING+1];

        h_uint16 tcp_port;
        h_uint16 udp_port;

        char version[LEN_MAX_VERSION_STRING+1];

        h_uint8 network_type;
        h_uint8 network_mode;
        h_uint8 wifi_mode;
        h_uint8 dhcp_status;

        struct timeval tv;
        h_int64 i64;
        h_uint64 u64;
        int value;
        int ecode ;

        mr_configure() :
            status(0),
            s_ip(0), s_netmask(0), s_gateway(0), s_dns(0),
            d_ip(0), d_netmask(0), d_gateway(0), d_dns(0),
            tcp_port(0), udp_port(0),
            network_type(0), network_mode(0), wifi_mode(0), dhcp_status(0),
            i64(0), u64(0), value(0), ecode(0)
        {
            memset( macaddr, LEN_MAX_MACADDR_STRING+1, 0 );
            memset( domain, LEN_MAX_DOMAIN_STRING+1, 0 );
            memset( version, LEN_MAX_VERSION_STRING+1, 0 );
            tv.tv_sec = 0;
            tv.tv_usec = 0;
        }

        mr_configure( const mr_configure& info )
        {
            status = info.status;

            s_ip = info.s_ip;
            s_netmask = info.s_netmask;
            s_gateway = info.s_gateway;
            s_dns = info.s_dns;

            d_ip = info.d_ip;
            d_netmask = info.d_netmask;
            d_gateway = info.d_gateway;
            d_dns = info.d_dns;

            memcpy( macaddr, info.macaddr, sizeof(info.macaddr) );
            memcpy( domain, info.domain, sizeof(info.domain) );


            tcp_port = info.tcp_port;
            udp_port = info.udp_port;

            memcpy( version, info.version, sizeof(info.macaddr) );

            network_type = info.network_type;
            network_mode = info.wifi_mode;
            wifi_mode = info.wifi_mode;
            dhcp_status = info.dhcp_status;

            tv = info.tv;

            i64 = info.i64;
            u64 = info.u64;
            value = info.value;
            ecode = info.ecode;
        }

        mr_configure& operator = ( const mr_configure& info )
        {
            status = info.status;

            s_ip = info.s_ip;
            s_netmask = info.s_netmask;
            s_gateway = info.s_gateway;
            s_dns = info.s_dns;

            d_ip = info.d_ip;
            d_netmask = info.d_netmask;
            d_gateway = info.d_gateway;
            d_dns = info.d_dns;

            memcpy( macaddr, info.macaddr, sizeof(info.macaddr) );
            memcpy( domain, info.domain, sizeof(info.domain) );


            tcp_port = info.tcp_port;
            udp_port = info.udp_port;

            memcpy( version, info.version, sizeof(info.macaddr) );

            network_type = info.network_type;
            network_mode = info.network_mode;
            wifi_mode = info.wifi_mode;
            dhcp_status = info.dhcp_status;

            tv = info.tv;

            i64 = info.i64;
            u64 = info.u64;
            value = info.value;
            ecode = info.ecode;
            return *this;
        }

    } mr_configure;



    typedef struct power_board_status
    {
        bool switch_;         // True: open, False: close
        bool router_;         // True: open, False: close
        bool locate_;         // True: open, False: close
        bool microphone_;     // True: open, False: close
        bool camera_;         // True: open, False: close
        bool preload_;        // True: open, False: close
        bool source_;         // True: battery, False: supply.
        bool battery_charge_; // True: charge, False: discharge.
        bool battery_status_; // True: full, False: un-full.
        bool internet_;       // True: internet, False: no internet.
        bool battery_connect_;        // True: battery connected, false: battery disconnected.
        bool battery_control_;        // True: forced, false: temperature.

        power_board_status() :
            switch_(false), router_(false), locate_(false),
            microphone_(false), camera_(false), preload_(false), source_(false),
            battery_charge_(false), battery_status_(false),
            internet_(false), battery_connect_(false), battery_control_(false)
        {}
    } power_board_status;

    typedef struct power_board_status_group
    {
        h_int16 temperature_; // *0.1 ℃

#ifdef HDTAS_WINDOWS
        template<typename F, typename S>
        struct inner_pair {
            F first;
            S second;
        };
        inner_pair<h_uint16, h_uint8> battery_;  // Voltage and capacity.
        inner_pair<h_uint16, h_uint16> camera_;  // Voltage and current.
        inner_pair<h_uint16, h_uint16> locate_;  // Voltage and current.
        inner_pair<h_uint16, h_uint16> router_;  // Voltage and current.
        inner_pair<h_uint16, h_uint16> switch_;  // Voltage and current.
        inner_pair<h_uint16, h_uint16> preload_; // Voltage and current.
#else
        std::pair<h_uint16, h_uint8> battery_;  // Voltage and capacity.
        std::pair<h_uint16, h_uint16> camera_;  // Voltage and current.
        std::pair<h_uint16, h_uint16> locate_;  // Voltage and current.
        std::pair<h_uint16, h_uint16> router_;  // Voltage and current.
        std::pair<h_uint16, h_uint16> switch_;  // Voltage and current.
        std::pair<h_uint16, h_uint16> preload_; // Voltage and current.
#endif

        h_uint8 auto_report_;
        h_uint8 auto_report_interval_;

        power_board_status_group() :
            temperature_(0), auto_report_(0), auto_report_interval_(0)
        {}

        power_board_status_group( const power_board_status_group& group )
        {
            this->temperature_ = group.temperature_;
            this->battery_ = group.battery_;
            this->camera_ = group.camera_;
            this->locate_ = group.locate_;
            this->router_ = group.router_;
            this->switch_ = group.switch_;
            this->preload_ = group.preload_;
            this->auto_report_ = group.auto_report_;
            this->auto_report_interval_ = group.auto_report_interval_;
        }

        power_board_status_group& operator=( const power_board_status_group& group )
        {
            this->temperature_ = group.temperature_;
            this->battery_ = group.battery_;
            this->camera_ = group.camera_;
            this->locate_ = group.locate_;
            this->router_ = group.router_;
            this->switch_ = group.switch_;
            this->preload_ = group.preload_;
            this->auto_report_ = group.auto_report_;
            this->auto_report_interval_ = group.auto_report_interval_;
            return *this;
        }
    } power_board_status_group;
}

#endif //HDTAS_STRUCT_H
