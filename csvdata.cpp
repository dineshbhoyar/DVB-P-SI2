/*
 * File:   csvdata.cpp
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



#include "csvdata.h"
#include "tsreader.h"
#include "dvbdumpreader.h"
#include "csvreader.h"


csvdata::csvdata(QObject *parent) : QObject(parent)
{

}

void csvdata::setSource(QString filepath)
{
    try{
        QUrl path(filepath);
        qDebug() << path.fileName();
        if( path.fileName().endsWith(".csv",Qt::CaseInsensitive)){
            CSVReader parser{};
            parser.Set(path);
            parser.Parse();
            data.clear();
            data = parser.Get();
            fdata.clear();
            fdata = parser.GetFMap();
            qDebug() <<" got network name " << parser.GetNetworkName().c_str();
            NetworkName= QString::fromStdString(  parser.GetNetworkName());
            qDebug() <<" NetworkName " << NetworkName;
        }else if( path.fileName().endsWith(".ts",Qt::CaseInsensitive)){
            TSReader parser{};
            parser.Set(path);
            connect(&parser,&TSReader::onNetworkNameChange,this,&csvdata::onNetworkNameChangeSlot);
            connect(&parser,&TSReader::onPrograsessChange,this,&csvdata::onPrograsessChangeSlot);
            connect(&parser,&TSReader::onStatusChange,this,&csvdata::onStatusChangeSlot);
            parser.Parse();
            data.clear();
            //            connect(&parser,&TSReader::ChannelsInstance,this,&csvdata::ChannelsInstanceSlot);
            //            connect(&parser,&TSReader::FreqInstance,this,&csvdata::FreqInstanceSlot);
            data=parser.Get();
            //            disconnect(&parser,&TSReader::ChannelsInstance,this,&csvdata::ChannelsInstanceSlot);
            //            disconnect(&parser,&TSReader::FreqInstance,this,&csvdata::FreqInstanceSlot);
            fdata.clear();
            fdata = parser.GetFMap();
            qDebug() <<" got network name " << parser.GetNetworkName().c_str();
            NetworkName= QString::fromStdString(  parser.GetNetworkName());
            qDebug() <<" NetworkName " << NetworkName;
            disconnect(&parser,&TSReader::onNetworkNameChange,this,&csvdata::onNetworkNameChangeSlot);
            disconnect(&parser,&TSReader::onPrograsessChange,this,&csvdata::onPrograsessChangeSlot);
            disconnect(&parser,&TSReader::onStatusChange,this,&csvdata::onStatusChangeSlot);
        }else if ( path.fileName().endsWith(".dump",Qt::CaseInsensitive) ){
            DVBDumpReader parser{};
            parser.Set(path);
            parser.Parse();
            data.clear();
            data=parser.Get();
            fdata.clear();
            fdata = parser.GetFMap();
            qDebug() <<" got network name " << parser.GetNetworkName().c_str();
            NetworkName= QString::fromStdString(  parser.GetNetworkName());
            qDebug() <<" NetworkName " << NetworkName;
        }else{
            QUrl url (filepath);
            QFileInfo finfo(url.path().replace("\\\\\\",""));
            if(finfo.isDir()){
                DVBDumpReader parser{};
                parser.Set(path);
                parser.Parse();
                data.clear();
                fdata.clear();
                fdata = parser.GetFMap();
                data=parser.Get();
                qDebug() <<" got network name " << parser.GetNetworkName().c_str();
                NetworkName= QString::fromStdString(  parser.GetNetworkName());
            }else{
                qDebug() << "file not handled ";
            }
        }
#if 1
        if (data.size() !=0){
            tChannel.clear();

            for(auto & value : data){
                // ProgrammeInfo& row = value.second;
                if(!value.second.isEmpty())
                    tChannel.addChannelInfo(ChannelInfo(value.second.Name,value.second.fInfo.QAM,
                                                        value.second.fInfo.Frequency,
                                                        value.second.fInfo.SymbolRate,
                                                        value.second.fInfo.FEC_inner,
                                                        value.second.fInfo.FEC_outer,
                                                        value.second.PROGID,
                                                        value.second.APID,value.second.VPID,
                                                        value.second.RPID,
                                                        value.second.PMT,value.second.ATYPE,
                                                        value.second.VTYPE,
                                                        value.second.SID,value.second.EPG,
                                                        value.second.StreamID,
                                                        value.second.Encrypted,
                                                        value.second.NetworkID,
                                                        value.second.Lang,
                                                        value.second.running_state,
                                                        value.second.service_type));
                /*if(!value.second.fInfo.isEmpty())
                    tParams.addTuningParametr(TuningParametr(value.second.fInfo.QAM,
                                                             value.second.fInfo.Frequency,
                                                             value.second.fInfo.SymbolRate,
                                                             value.second.fInfo.FEC_inner,
                                                             value.second.fInfo.FEC_outer));*/
            }
        }
        if(fdata.size() != 0){
            tParams.clear();
            for (auto & f : fdata){
                if(!f.second.isEmpty())
                    switch (f.second.type) {
                    case CABLE:
                    {
                        qDebug() << " cable : freq "<< f.second.Frequency;
                        tParams.addTuningParametr(TuningParametr(f.second.QAM,
                                                                 f.second.Frequency,
                                                                 f.second.SymbolRate,
                                                                 f.second.FEC_inner,
                                                                 f.second.FEC_outer));
                    }
                        break;
                    case SATELATE:
                    {
                        qDebug() << " satelate : freq "<< f.second.Frequency;
                        tParams.addTuningParametr(TuningParametr(f.second.Frequency,
                                                                 f.second.orbital_position,
                                                                 f.second.west_east_flag,
                                                                 f.second.polarization,
                                                                 f.second.roll_off,
                                                                 f.second.modulation_system,
                                                                 f.second.modulation_type,
                                                                 f.second.SymbolRate,
                                                                 f.second.FEC_inner));
                    }
                        break;
                    case TERRESTRIAL:
                    {
                        tParams.addTuningParametr(TuningParametr(f.second.Frequency,
                                                                 f.second.bandwidth,
                                                                 f.second.priority,
                                                                 f.second.Time_Slicing_indicator,
                                                                 f.second.MPE_FEC_indicator,
                                                                 f.second.constellation,
                                                                 f.second.hierarchy_information,
                                                                 f.second.code_rate_HP_stream,
                                                                 f.second.code_rate_LP_stream,
                                                                 f.second.guard_interval,
                                                                 f.second.transmission_mode,
                                                                 f.second.other_frequency_flag));
                    }
                        break;
                    default:
                        break;
                    }

            }
        }else{
            qDebug() << "error getting freqency map ";
        }
#endif
    }catch(std::exception& e){
        qDebug()<<"error : "<< e.what();
    }catch(...){
        qDebug()<<"unknown exception";
    }
}



bool csvdata::dataReady() const
{
    return dataState;
}
void csvdata::onNetworkNameChangeSlot(QString name){
    emit networkNameChange(name);
};
void csvdata::onPrograsessChangeSlot(double size){
    //qDebug()<<" csvdata setting progress " << size;
    emit prograsessChange(size);
};
void csvdata::onStatusChangeSlot(QString status){
    emit statusChange(status);
};
//QAbstractItemModel &csvdata::theModel()
//{

//}

void csvdata::setDataReady(const bool &value)
{
    dataState=value;
}

void csvdata::ChannelsInstanceSlot(ProgrammeInfo p)
{
    qDebug() <<" updating pid " << p.PROGID ;
    if(!p.isEmpty())
        tChannel.addChannelInfo(ChannelInfo(p.Name,p.fInfo.QAM,
                                            p.fInfo.Frequency,
                                            p.fInfo.SymbolRate,
                                            p.fInfo.FEC_inner,
                                            p.fInfo.FEC_outer,
                                            p.PROGID,p.APID,p.VPID,
                                            p.RPID,
                                            p.PMT,p.ATYPE,
                                            p.VTYPE,
                                            p.SID,p.EPG,
                                            p.StreamID,
                                            p.Encrypted,
                                            p.NetworkID,
                                            p.Lang,
                                            p.running_state,
                                            p.service_type));

}

void csvdata::FreqInstanceSlot(FreqInfo f)
{
    qDebug() << " updating freq ***********" << f.Frequency ;
    if(f.isEmpty())
        switch (f.type) {
        case CABLE:
            tParams.addTuningParametr(TuningParametr(f.QAM,
                                                     f.Frequency,
                                                     f.SymbolRate,
                                                     f.FEC_inner,
                                                     f.FEC_outer));
            break;
        case SATELATE:
            tParams.addTuningParametr(TuningParametr(f.Frequency,
                                                     f.orbital_position,
                                                     f.west_east_flag,
                                                     f.polarization,
                                                     f.roll_off,
                                                     f.modulation_system,
                                                     f.modulation_type,
                                                     f.SymbolRate,
                                                     f.FEC_inner));
            break;
        case TERRESTRIAL:
            tParams.addTuningParametr(TuningParametr(f.Frequency,
                                                     f.bandwidth,
                                                     f.priority,
                                                     f.Time_Slicing_indicator,
                                                     f.MPE_FEC_indicator,
                                                     f.constellation,
                                                     f.hierarchy_information,
                                                     f.code_rate_HP_stream,
                                                     f.code_rate_LP_stream,
                                                     f.guard_interval,
                                                     f.transmission_mode,
                                                     f.other_frequency_flag));
            break;
        default:
            break;
        }

}

TuningParametrModel::TuningParametrModel(QObject *parent): QAbstractItemModel{parent}
{

}

void TuningParametrModel::addTuningParametr(const TuningParametr& params)
{
    if(! m_tuningparms.contains(params)){
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_tuningparms << params;
        //this->sort(SymbolRate,Qt::DescendingOrder);
        endInsertRows();
    }
}
void TuningParametrModel::clear(){
    beginResetModel();
    while (!m_tuningparms.isEmpty())
        m_tuningparms.removeFirst();
    endResetModel();
}

int TuningParametrModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_tuningparms.count();

}
QModelIndex TuningParametrModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!parent.isValid()) // we should return a valid QModelIndex for root elements (whose parent
        return this->createIndex(row,column); // is invalid) only, because our model is flat
    else
        return QModelIndex();
}

QModelIndex TuningParametrModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}
int TuningParametrModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TuningParametrModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_tuningparms.count())
        return QVariant();

    const TuningParametr &tparams = m_tuningparms[index.row()];
    switch (role)
    {
    case Qt::DisplayRole: return tparams.freq();break;
    case Type : return tparams.type();break;
    case QAM: return tparams.qam();break;
    case Frequency: return tparams.freq();break;
    case SymbolRate : return tparams.symbol();break;
    case FEC_INNER:return tparams.fec_inner();break;
    case FEC_OUTER:return tparams.fec_outer();break;
    case Bandwidth:return tparams.bandwidth();break;
    case Priority : return tparams.priority();break;
    case Time_Slicing_indicator : return tparams.Time_Slicing_indicator();break;
    case MPE_FEC_indicator : return tparams.MPE_FEC_indicator();break;
    case Constellation:return tparams.constellation();break;
    case Hierarchy_information:return tparams.hierarchy_information();break;
    case Code_rate_HP_stream:return tparams.code_rate_HP_stream();break;
    case Code_rate_LP_stream:return tparams.code_rate_LP_stream();break;
    case Guard_interval:return tparams.guard_interval();break;
    case Transmission_mode:return tparams.transmission_mode();break;
    case Other_frequency_flag:return tparams.other_frequency_flag();break;
    case Orbital_position:return tparams.orbital_position();break;
    case West_east_flag:return tparams.west_east_flag();break;
    case Polarization:return tparams.polarization();break;
    case Roll_off:return tparams.roll_off();break;
    case Modulation_system:return tparams.modulation_system();break;
    case Modulation_type:return tparams.modulation_type();break;
    default : return QVariant(); break;
    }
    return QVariant();
}

QHash<int, QByteArray> TuningParametrModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Type] ="type";
    roles[Frequency] = "frequency";
    roles[QAM] = "qam";
    roles[SymbolRate]= "symbolrate";
    roles[FEC_INNER]="fec_inner";
    roles[FEC_OUTER]="fec_outer";
    roles[Bandwidth]= "bandwidth";
    roles[Priority]="priority";
    roles[Time_Slicing_indicator]="time_slicing_indicator";
    roles[MPE_FEC_indicator]="MPE_FEC_indicator";
    roles[Constellation]="constellation";
    roles[Hierarchy_information]="hierarchy_information";
    roles[Code_rate_HP_stream]="code_rate_HP_stream";
    roles[Code_rate_LP_stream]="code_rate_LP_stream";
    roles[Guard_interval]="guard_interval";
    roles[Transmission_mode]="transmission_mode";
    roles[Other_frequency_flag]="other_frequency_flag";
    roles[Orbital_position]="orbital_position";
    roles[West_east_flag]="west_east_flag";
    roles[Polarization]="polarization";
    roles[Roll_off]="roll_offl";
    roles[Modulation_system]="modulation_system";
    roles[Modulation_type]="modulation_type";
    return roles;

}



ChannelInfoModel::ChannelInfoModel(QObject *parent):QAbstractListModel{parent}
{

}

void ChannelInfoModel::addChannelInfo(const ChannelInfo &params)
{
    if(params.cname().length()){
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_channelinfo << params;
        endInsertRows();
    }

}
void ChannelInfoModel::clear()
{
    beginResetModel();
    while(!m_channelinfo.isEmpty())
        m_channelinfo.removeFirst();
    endResetModel();
}
int ChannelInfoModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_channelinfo.count();
}

QVariant ChannelInfoModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_channelinfo.count())
        return QVariant();

    const ChannelInfo &cparams = m_channelinfo[index.row()];
    if (role == Name || role == Qt::DisplayRole)
        return cparams.cname();
    else if (role == QAM)
        return cparams.qam();
    else if (role == Frequency)
        return cparams.frequency();
    else if (role == SymbolRate)
        return cparams.symbol();
    else if (role == FEC_INNER)
        return cparams.fec_inner();
    else if (role == FEC_OUTER)
        return cparams.fec_outer();
    else if (role == PROGID)
        return cparams.progid();
    else if (role == APID)
        return cparams.apid();
    else if (role == VPID)
        return cparams.vpid();
    else if (role == RPID)
        return cparams.rpid();
    else if (role == PMT)
        return cparams.pmt();
    else if (role == ATYPE)
        return cparams.atype();
    else if (role == VTYPE)
        return cparams.vtype();
    else if (role == SID)
        return cparams.sid();
    else if (role ==EPG)
        return cparams.epg();
    else if (role == StreamID)
        return cparams.streamid();
    else if (role ==Encrypted)
        return cparams.encrypted();
    else if (role == NetworkID)
        return cparams.networkid();
    else if (role == Lang)
        return cparams.lang();
    else if (role ==ServiceDescription)
        return cparams.service_type();
    else if (role ==ServiceState)
        return cparams.running_state();
    return QVariant();
}

QHash<int, QByteArray> ChannelInfoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Name] = "cname";
    roles[QAM] = "qam";
    roles[Frequency] = "frequency";
    roles[SymbolRate]= "symbolrate";
    roles[FEC_INNER]="fec_inner";
    roles[FEC_OUTER]="fec_outer";
    roles[PROGID]="progid";
    roles[APID]="apid";
    roles[VPID]="vpid";
    roles[RPID]="rpid";
    roles[PMT]="pmt";
    roles[ATYPE]="atype";
    roles[VTYPE]="vtype";
    roles[SID]="sid";
    roles[EPG]="epg";
    roles[StreamID]="streamid";
    roles[Encrypted]="encrypted";
    roles[NetworkID]="netwotkid";
    roles[Lang]="lang";
    roles[ServiceState]="s_state";
    roles[ServiceDescription]="s_desc";
    return roles;

}

bool TuningParametr::operator==( const TuningParametr &lhs)
{
    return (fec_inner() == lhs.fec_inner() &&
            fec_outer() == lhs.fec_outer() &&
            freq() == lhs.freq()&&
            qam() == lhs.qam()&&
            symbol() == lhs.symbol());
}

FilterSortModel::FilterSortModel(QObject *parent):QSortFilterProxyModel{parent}
{
    setSortOrder(false);
}

FilterSortModel::~FilterSortModel()
{

}

void FilterSortModel::setFilterString(QString string)
{
    this->setFilterCaseSensitivity(Qt::CaseInsensitive);
    this->setFilterFixedString(string);
}

void FilterSortModel::setSortOrder(bool checked)
{
    if(checked)
    {
        this->sort(Qt::UserRole+2, Qt::DescendingOrder);
    }
    else
    {
        this->sort(Qt::UserRole+2, Qt::AscendingOrder);
    }
}


