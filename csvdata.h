/*
 * File:   csvdata.h
 * Author: Dinesh M. Bhoyar
 *
 * Created on 6 10 2017
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#ifndef CSVDATA_H
#define CSVDATA_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QUrl>
#include <QAbstractListModel>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
#include <functional>
#include <memory>
#include <exception>
#include <thread>
#include "fileparser.h"



///usr/lib/x86_64-linux-gnu/Qt5.9.1/Examples/Qt-5.9.1/quick/models/abstractitemmodel/model.cpp
class TuningParametr
{
public:
    TuningParametr(const QString &qam,
                   const QString &freq,
                   const QString &symbol,
                   const QString &fec_inner,
                   const QString &fec_outer
                   ):m_type{1},m_qam{qam},m_freq{freq},
        m_symbol{symbol},m_fec_inner{fec_inner},
        m_fec_outer{fec_outer}
    {

    }
    TuningParametr( const QString& centre_frequency,
                    const QString& bandwidth,
                    const QString& priority,
                    const QString& Time_Slicing_indicator,
                    const QString& MPE_FEC_indicator,
                    const QString& constellation,
                    const QString& hierarchy_information,
                    const QString& code_rate_HP_stream,
                    const QString& code_rate_LP_stream,
                    const QString& guard_interval,
                    const QString& transmission_mode,
                    const QString& other_frequency_flag):m_type{2},m_freq{centre_frequency},
        m_bandwidth{bandwidth},m_priority{priority},
        m_Time_Slicing_indicator{Time_Slicing_indicator},
        m_MPE_FEC_indicator{MPE_FEC_indicator},
        m_constellation{constellation},
        m_hierarchy_information{hierarchy_information},
        m_code_rate_HP_stream{code_rate_HP_stream},
        m_code_rate_LP_stream{code_rate_LP_stream},
        m_guard_interval{guard_interval},
        m_transmission_mode{transmission_mode},
        m_other_frequency_flag{other_frequency_flag}
    {

    }
    TuningParametr(const QString& frequency,
                   const QString& orbital_position,
                   const QString& west_east_flag,
                   const QString& polarization,
                   const QString& roll_off,
                   const QString& modulation_system,
                   const QString& modulation_type,
                   const QString& symbol,
                   const QString& fec_inner
                   ):m_type{3},m_freq{frequency},m_symbol{symbol},
        m_fec_inner{fec_inner},m_orbital_position{orbital_position},
        m_west_east_flag{west_east_flag},m_polarization{polarization},m_roll_off{roll_off},
        m_modulation_system{modulation_system},m_modulation_type{modulation_type}
    {

    }

    quint32 type() const{return m_type;};
    QString qam() const{return m_qam; }

    QString freq() const{ return m_freq;}

    QString symbol() const{return m_symbol;}

    QString fec_inner() const{return m_fec_inner; }

    QString fec_outer() const{return m_fec_outer; }
    QString bandwidth() const{return m_bandwidth;}
    QString priority() const {return m_priority;}
    QString Time_Slicing_indicator() const {return m_Time_Slicing_indicator;}
    QString MPE_FEC_indicator() const {return m_MPE_FEC_indicator;}
    QString constellation() const { return m_constellation;}
    QString hierarchy_information() const { return  m_hierarchy_information;}
    QString code_rate_HP_stream()const { return  m_code_rate_HP_stream;}
    QString code_rate_LP_stream() const { return  m_code_rate_LP_stream;}
    QString guard_interval() const { return  m_guard_interval;}
    QString transmission_mode() const { return  m_transmission_mode;}
    QString other_frequency_flag()const{ return m_other_frequency_flag;}
    //satelite
    QString orbital_position()const { return  m_orbital_position;}
    QString west_east_flag() const{ return m_west_east_flag;}
    QString polarization() const { return  m_polarization;}
    QString roll_off()const{ return m_roll_off;}
    QString modulation_system() const { return  m_modulation_system;}
    QString modulation_type() const { return  m_modulation_type;}
    bool operator==(const TuningParametr& lhs);
private:
    qint32 m_type;
    QString m_qam;
    QString m_freq;
    QString m_symbol;
    QString m_fec_inner;
    QString m_fec_outer;
    //terrestrial
    QString m_bandwidth,m_priority,m_Time_Slicing_indicator,m_MPE_FEC_indicator;
    QString m_constellation,m_hierarchy_information,m_code_rate_HP_stream;
    QString m_code_rate_LP_stream,m_guard_interval,m_transmission_mode,m_other_frequency_flag;
    //satelite
    QString m_orbital_position,m_west_east_flag,m_polarization,m_roll_off,m_modulation_system;
    QString m_modulation_type;
};

//http://doc.qt.io/qt-5/qtwidgets-itemviews-simpletreemodel-example.html for refrance
//use a tree model to represent data in application
enum TuningParametrRole{
    Type=Qt::UserRole+1,
    QAM=Type+1,
    Frequency=QAM+1,
    SymbolRate=Frequency+1,
    FEC_INNER=SymbolRate+1,
    FEC_OUTER=FEC_INNER+1,
    Bandwidth=FEC_OUTER+1,
    Priority=Bandwidth+1,
    Time_Slicing_indicator=Priority+1,
    MPE_FEC_indicator=Time_Slicing_indicator+1,
    Constellation=MPE_FEC_indicator+1,
    Hierarchy_information=Constellation+1,
    Code_rate_HP_stream=Hierarchy_information+1,
    Code_rate_LP_stream=Code_rate_HP_stream+1,
    Guard_interval=Code_rate_LP_stream+1,
    Transmission_mode=Guard_interval+1,
    Other_frequency_flag=Transmission_mode+1,
    Orbital_position=Other_frequency_flag+1,
    West_east_flag=Orbital_position+1,
    Polarization=West_east_flag+1,
    Roll_off=Polarization+1,
    Modulation_system=Roll_off+1,
    Modulation_type=Modulation_system+1
};
class TuningParametrModel:public /*QAbstractListModel*/QAbstractItemModel{
    Q_OBJECT
public:

    TuningParametrModel(QObject*parent=0);
    void addTuningParametr(const TuningParametr &params);
    void clear();
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int,QByteArray>roleNames()const;
private:
    QList<TuningParametr> m_tuningparms;
};

class ChannelInfo
{
public:
    ChannelInfo(const QString& Name,
                const QString& QAM,
                const QString& Frequency,
                const QString& Symbol,
                const QString& FEC_inner,
                const QString& FEC_outer,
                const QString& PROGID,
                const QString& APID,
                const QString& VPID,
                const QString& RPID,
                const QString& PMT,
                const QString& ATYPE,
                const QString& VTYPE,
                const QString& SID,
                const QString& EPG,
                const QString& StreamID,
                const QString& Encrypted,
                const QString& NetworkID,
                const QString& Lang,
                const QString& running_state,
                const QString& service_type):
        m_cname{Name},m_qam{QAM},m_frequency{Frequency},m_symbol{Symbol},m_fec_inner{FEC_inner},
        m_fec_outer{FEC_outer},m_progid{PROGID}, m_apid{APID}, m_vpid{VPID}, m_rpid{RPID},
        m_pmt{PMT},m_atype{ATYPE}, m_vtype{VTYPE},m_sid{SID},m_epg{EPG},
        m_streamid{StreamID},m_encrypted{Encrypted},m_networkid{NetworkID},m_lang{Lang},
        m_running_state{running_state},m_service_type{service_type}
    {};
    QString cname()const{ return m_cname;};
    QString qam() const{ return m_qam;};
    QString frequency() const { return m_frequency;};
    QString symbol()const{ return m_symbol;};
    QString fec_inner() const{ return m_fec_inner;};
    QString fec_outer() const{ return m_fec_outer;};
    QString progid()const{ return m_progid;};
    QString apid()const{ return m_apid;};
    QString vpid()const{ return m_vpid;};
    QString rpid()const{ return m_rpid;};
    QString pmt()const{ return m_pmt;};
    QString atype()const{ return m_atype;};
    QString vtype()const{ return m_vtype;};
    QString sid()const{ return m_sid;};
    QString epg()const{ return m_epg;};
    QString streamid()const{ return m_streamid;};
    QString encrypted()const{ return m_encrypted;};
    QString networkid()const{ return m_networkid;};
    QString lang()const{ return m_lang;};
    QString running_state()const{ return m_running_state;};
    QString service_type()const{ return m_service_type;};

private:
    QString m_cname,m_qam,m_frequency,m_symbol,m_fec_inner,m_fec_outer;
    QString m_progid, m_apid, m_vpid, m_rpid, m_pmt,m_atype, m_vtype,m_sid,m_epg;
    QString m_streamid,m_encrypted,m_networkid,m_lang;
    QString m_running_state,m_service_type;

};
class ChannelInfoModel:public QAbstractListModel{
    Q_OBJECT
public:
    enum ChannelInfoRole{
        Name=Qt::UserRole+1,
        QAM=Name+1,
        Frequency=QAM+1,
        SymbolRate=Frequency+1,
        FEC_INNER=SymbolRate+1,
        FEC_OUTER=FEC_INNER+1,
        PROGID=FEC_OUTER+1,
        APID=PROGID+1,
        VPID=APID+1,
        RPID=VPID+1,
        PMT=RPID+1,
        ATYPE=PMT+1,
        VTYPE=ATYPE+1,
        SID=VTYPE+1,
        EPG=SID+1,
        StreamID=EPG+1,
        Encrypted=StreamID+1,
        NetworkID=Encrypted+1,
        Lang=NetworkID+1,
        ServiceState=Lang+1,
        ServiceDescription=ServiceState+1
    };
public:
    explicit ChannelInfoModel(QObject *parent = 0);
    void addChannelInfo(const ChannelInfo &params);
    void clear();
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
protected:
    QHash<int,QByteArray>roleNames() const;
private:
    QList<ChannelInfo> m_channelinfo;
};

class csvdata : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool dataReady READ dataReady WRITE setDataReady NOTIFY dataReadyChanged)
    // QAbstractItemModel m_model;
    bool dataState;
    QList<QStringList> channelParams ;
    QList<QStringList> bouquetList;
    QList<QStringList> lcnMap;
    std::map<uint16_t,ProgrammeInfo> data;
    std::map<double,FreqInfo> fdata;
public:
    ChannelInfoModel tChannel;
    TuningParametrModel tParams;
    QString NetworkName;
    explicit csvdata(QObject *parent = nullptr);

    Q_INVOKABLE void setSource(QString filepath);

    //Q_INVOKABLE QAbstractItemModel &theModel();
    bool dataReady() const;
    void setDataReady(const bool &value);
signals:
    void dataReadyChanged();
    void networkNameChange(QString name);
    void prograsessChange(double size);
    void statusChange(QString status);
public slots:
    void ChannelsInstanceSlot(ProgrammeInfo p);
    void FreqInstanceSlot(FreqInfo f);
    void onNetworkNameChangeSlot(QString name);
    void onPrograsessChangeSlot(double size);
    void onStatusChangeSlot(QString status);
};

class FilterSortModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    FilterSortModel(QObject* parent=nullptr);
    ~FilterSortModel();
    Q_INVOKABLE void setFilterString(QString string);

    Q_INVOKABLE void setSortOrder(bool checked);
};



#endif // CSVDATA_H
