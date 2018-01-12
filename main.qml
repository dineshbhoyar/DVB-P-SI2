import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2

//import Qt.labs.platform 1.0

ApplicationWindow {
    id:app
    visible: true
    width: 640
    height: 500

    //app window can not shrink less than this
    minimumWidth:640
    minimumHeight: 500

    property int margin: 4
    property string fileSelected: appfiledialog.fileUrl
    onFileSelectedChanged:   console.log('file selected ' + appfiledialog.fileUrl)

    //app title
    title: qsTr("DVB-P-SI2")

    MessageDialog{
        id:aboutDialog
        title: qsTr("About")
        text: qsTr("Author: Dinesh M. Bhoyar  <br> email:- bhoyar.dinesh@gmail.com")
        onAccepted: {
            console.log(" ok ")
        }
    }

    MessageDialog{
        id:versionDialog
        title: qsTr("Version")
        text: qsTr("Version - 1.0.0")
        onAccepted: {
            console.log(" ok ")
        }
    }
    menuBar: MenuBar{
        id:appmenubar
        Menu{
            title: qsTr("&File")

            MenuItem {
                text:qsTr("Open TS")
                onTriggered:{
                    appfiledialog.nameFilters=["TS Files (*.ts)"," All Files (*)"]
                    appfiledialog.open()
                }
            }
            MenuSeparator{}
            MenuItem {
                text:qsTr("Open DVBDump")
                onTriggered:{
                    appfiledialog.nameFilters=["Dump Files (*.dump)"," All Files (*)"]
                    appfiledialog.open()
                }
            }
            MenuItem {
                text:qsTr("Open DVBDump(folder)")
                onTriggered:{
                    appfiledialog.nameFilters=[" All Files (*)"]
                    appfiledialog.selectFolder = true
                    appfiledialog.selectMultiple =false
                    appfiledialog.selectExisting = true
                    appfiledialog.open()
                }
            }
            MenuSeparator{}
            MenuItem {
                text:qsTr("Open CSV")
                onTriggered:{
                    appfiledialog.nameFilters=["CSV Files (*.csv)"," All Files (*)"]
                    appfiledialog.open()
                    //fileSelected=appfiledialog.fileUrl
                }
            }
            //            MenuItem{text:"Close"}
            MenuSeparator{}
            MenuItem{
                text:qsTr("&Exit")
                onTriggered: Qt.quit()
            }

        }

        Menu{
            title: qsTr("&Config")
            MenuItem{
                text: qsTr("Enable NIT Other")
                checkable: true
                checked:true
            }
            MenuItem{
                text:qsTr("Enable SDT Other")
                checkable: true
                checked:true
            }
        }
        Menu{
            title: qsTr("&Help")
            MenuItem{
                text:qsTr("About")
                onTriggered: aboutDialog.open()
            }
            MenuItem{
                text:qsTr("Version")
                onTriggered: versionDialog.open()
            }
        }
    }
    FileDialog{
        id:appfiledialog
        folder: shortcuts.home
        //nameFilters: [ " All Files (*)", "TS Files (*.ts)", "Dump Files (*.dump)","CSV Files (*.csv)"]

    }
    toolBar: ToolBar{
        id:apptoolbar
        KeyNavigation.tab: appFreqListView
        RowLayout{
            anchors.fill: parent
            ToolButton{
                text:qsTr("Play")
                iconSource: "images/play.png"
                onClicked: {
                    console.log( text+" button pressed  processing file ",fileSelected);
                    csv.setSource(fileSelected);
                }
            }

        }
    }
    /*
    Rectangle{
        id:appContent
        width: contentItem.maximumWidth
        height: contentItem.maximumHeigth
        anchors.fill: parent
        color: "white"
        //freq table and channel list
        SplitView{
            id:appSplitview
            orientation: Qt.Horizontal
            anchors.top: appContent.top
            anchors.left: appContent.left
            width:appContent.width
            height: appContent.height/2
            //implicitWidth: parent.width
            //implicitHeight: parent.height
            ScrollView{
                width:appSplitview.width/2
                height: appSplitview.height/2
                ListView{
                    id:freqView
                    anchors.fill: parent
                    orientation: Qt.Vertical
                    header:Text{text:"Frequency"}
                    footer:Text{text:"total"}
                    footerPositioning:ListView.OverlayFooter
                    model:tParams
                    //spacing: 1.0
                    focus:true
                    highlight: Rectangle {
                        color: "lightsteelblue"
                        border.color: "blue"
                        radius: 5
                    }
                    delegate: Rectangle {
                        width:freqView.width * .8
                        height: freqView.height/10
                        // border.color: "blue"
                        // radius: height/10
                        // color: "lightsteelblue"
                        function getImgSource(idx)
                        {
                            if(idx ==1)
                                return "images/cable.png"
                            else if (idx == 2)
                                return "images/terrestrial.png"
                            else if (idx == 3)
                                return "images/satellite-icon.png"
                        }
                        function freqUnit(idx)
                        {
                            if(idx ==1)
                                return " MHz"
                            else if (idx == 2)
                                return " Hz"
                            else if (idx == 3)
                                return " GHz"
                        }
                        Image {
                            id: iconlst
                            source: getImgSource(type)
                            anchors.left: parent.left+2
                            anchors.top: parent.top+2
                            height: parent.height -4
                            //anchors.centerIn: parent
                            //height: parent.height
                        }
                        Text {
                            anchors.left: iconlst.right
                            anchors.leftMargin: 5
                            anchors.verticalCenter: parent.verticalCenter
                            width: parent.width
                            id: lstelement
                            //anchors.fill: parent
                            text: frequency + freqUnit(type)
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked:{
                                freqView.currentIndex = index
                                switch(type){
                                case 1:

                                    description.text ="<b> Frequency : </b><i>"+frequency+" Mhz "
                                            +"</i><br><b> QAM : </b><i>"+ qam +
                                            "</i><br><b> SymbolRate : </b><i> "+symbolrate+" Msymbol/s"+
                                            "</i><br><b> FEC_inner : </b><i> "+fec_inner+
                                            "</i><br><b> FEC_outer : </b><i> "+fec_outer+"</i>"
                                    break;
                                case 2:

                                    description.text ="<b> Frequency : </b><i>"+frequency+" Hz "
                                            +"</i><br><b> Bandwidth : </b><i>"+ bandwidth +
                                            "</i><br><b> Time_Slicing_indicator : </b><i> "+time_slicing_indicator+
                                            "</i><br><b> MPE_FEC_indicator : </b><i> "+MPE_FEC_indicator+
                                            "</i><br><b> constellation : </b><i> "+constellation+

                                            "</i><br><b> hierarchy_information : </b><i> "+hierarchy_information+
                                            "</i><br><b> Code_rate_HP_stream : </b><i> "+code_rate_HP_stream+
                                            "</i><br><b> Code_rate_LP_stream : </b><i> "+code_rate_LP_stream+
                                            "</i><br><b> guard_interval : </b><i> "+guard_interval+
                                            "</i><br><b> transmission_mode : </b><i> "+transmission_mode+
                                            "</i><br><b> other_frequency_flag : </b><i> "+other_frequency_flag+
                                            "</i>"
                                    break;
                                case 3:

                                    description.text ="<b> Frequency : </b><i>"+frequency+" Ghz "
                                            +"</i><br><b> orbital_position : </b><i>"+orbital_position +"°"+
                                            "</i><br><b> SymbolRate : </b><i> "+symbolrate+" Msymbol/s"+
                                            "</i><br><b> FEC_inner : </b><i> "+fec_inner+
                                            "</i><br><b> west_east_flag : </b><i> "+west_east_flag+
                                            "</i><br><b> polarization : </b><i> "+polarization+
                                            "</i><br><b> roll_offl : </b><i> "+roll_offl+
                                            "</i><br><b> modulation_system : </b><i> "+modulation_system+
                                            "</i><br><b> modulation_type : </b><i> "+modulation_type+"</i>"
                                    break;
                                default:
                                    break;
                                }

                            }
                        }
                    }
                    onCurrentItemChanged: console.log(freqView.currentIndex + ' selected')

                    keyNavigationEnabled :true
                    Keys.onPressed: {
                        //console.log("list: " + event.key + " : " + event.text)
                        //if (event.key == Qt.Key_Left) console.log("Moving to the left");
                        //else if (event.key == Qt.Key_Right) console.log("Moving to the right");
                        if (event.key  == Qt.Key_Enter || event.key == Qt.Key_Return){
                            console.log("Enter : current index"+freqView.currentIndex)
                        }else if (event.key == Qt.Key_Down){
                            console.log("Down : current index"+freqView.currentIndex)
                        }else if (event.key == Qt.Key_Up){
                            console.log("Up : current index"+freqView.currentIndex)
                        }
                    }
                }
            }
            ScrollView{
                width:appSplitview.width/2
                height: appSplitview.height/2
                ListView{
                    id:channelView
                    anchors.fill: parent
                    orientation: Qt.Vertical
                    header:Text{text:"channels"}
                    footer:Text{text:"total"}
                    footerPositioning:ListView.OverlayFooter
                    model:tChannel
                    spacing: 1.0
                    focus:true
                    highlight: Rectangle {
                        color: "green"
                        border.color: "blue"
                        radius: height/10
                    }
                    delegate: Rectangle {
                        width:freqView.width * .8
                        height: freqView.height/10
                        border.color: "blue"
                        radius: height/10
                        color: "lightsteelblue"
                        Text {
                            width: parent.width
                            id: lstelement
                            anchors.fill: parent
                            text: cname+"("+progid+")"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                channelView.currentIndex = index
                                //listProperty(tChannel)
                                //console.log(tChannel.data(0,frequency))
                                description.text = "<b> Chnnel name : </b><i>"+cname+
                                        //"</i><br><b> QAM : </b><i>"+qam+
                                        "</i><br><b> Frequency :  </b><i>"+frequency+
                                        // "</i><br><b> Symbol Rate :  </b><i>"+symbolrate+
                                        //  "</i><br><b> FEC_inner :  </b><i>"+fec_inner+
                                        // "</i><br><b> FEC_outer :  </b><i>"+fec_outer+
                                        "</i><br><b> ServiceID :  </b><i>"+progid+
                                        "</i><br><b> Audio PID :  </b><i>"+apid+
                                        "</i><br><b> Video PID :  </b><i> "+vpid+
                                        "</i><br><b> R PID :  </b><i> "+rpid+
                                        "</i><br><b> PMT PID :  </b><i> "+pmt+
                                        "</i><br><b> Audio Type :  </b><i> "+atype+
                                        "</i><br><b> Video Type :  </b><i> "+vtype+
                                        "</i><br><b> Sequence ID :  </b><i> "+sid+
                                        "</i><br><b> EPG Available :  </b><i> "+epg+
                                        "</i><br><b> Stream ID :  </b><i> "+streamid+
                                        "</i><br><b> Emcripted :  </b><i>  "+encrypted+
                                        "</i><br><b> Network ID :  </b><i> "+netwotkid+
                                        "</i><br><b> Language :  </b><i> "+lang+
                                        "</i><br><b> Channel state :  </b><i> "+s_state+
                                        "</i><br><b> Channel description :  </b><i> "+s_desc
                            }
                        }
                    }
                    keyNavigationEnabled :true
                    Keys.onPressed: {
                        //console.log("list: " + event.key + " : " + event.text)
                        //if (event.key == Qt.Key_Left) console.log("Moving to the left");
                        //else if (event.key == Qt.Key_Right) console.log("Moving to the right");
                        if (event.key  == Qt.Key_Enter|| event.key == Qt.Key_Return){
                            console.log("Enter : current index"+channelView.currentIndex)
                        }else if (event.key == Qt.Key_Down){
                            console.log("Down : current index"+channelView.currentIndex)
                        }else if (event.key == Qt.Key_Up){
                            console.log("Up : current index"+channelView.currentIndex)
                        }
                    }
                }

            }
        }
        ScrollView {
            id: view
            anchors.top: appSplitview.bottom
            anchors.left: appContent.left
            width: appContent.width -3
            height: (appContent.height/2) -3
            Rectangle{
                id:scRect
                width: appContent.width -3
                height: appContent.height -3
                radius: height/20
                border.color: "green"
                //anchors.top: appSplitview.bottom
                //anchors.left: appContent.left
                //anchors.leftMargin: 3
                //anchors.topMargin: 3

                TextArea {
                    wrapMode: Text.WordWrap
                    anchors.fill: parent
                    readOnly: true
                    textFormat:TextEdit.RichText
                    id: description
                    text: qsTr("No description available")
                    focus: false
                }
            }
        }
    }*/
    ColumnLayout{
        id:appRegion
        anchors.fill: parent
        anchors.margins: margin
        GroupBox{
            Layout.fillWidth:  true
            Layout.fillHeight: true
            width: ((appRegion.width)-(margin*2))
            height: ((appRegion.height/2)-(margin*2))
            id:groupOne
            title: "Service Provider "

            RowLayout{
                id:appListLayout
                spacing: 10
                anchors.fill: parent

                //using List view insted to begain with

                Rectangle{
                    id:rect1
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    anchors.margins: margin
                    radius: 5
                    ListView{
                        id:appFreqListView
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        orientation: Qt.Vertical
                        visible: true
                        x:margin
                        y:margin
                        width: (rect1.width  - (margin*2))
                        height:  (rect1.height - (margin*2))
                        anchors.margins: margin

                        highlight: Rectangle{ color: "lightsteelblue" ;radius:5}
                        focus: true
                        //accept focus via tab button
                        activeFocusOnTab: true
                        //to enable updown nevigation
                        keyNavigationEnabled: true

                        onFocusChanged: {
                            console.log("focuse changed")
                        }

                        model: tParams
                        delegate:
                            Component{
                            Item {
                                id:listElementFreq
                                width: appFreqListView.width
                                height:  20
                                Column{
                                    Text {
                                        x:margin
                                        id:lstItem
                                        text: qsTr(frequency)
                                        color: listElementFreq.ListView.isCurrentItem ? "red" : "black"
                                    }
                                }
                                MouseArea {
                                    id: rect_area1
                                    z: 1
                                    hoverEnabled: false
                                    anchors.fill: parent
                                    onClicked: {
                                        console.log(" freq clicked")
                                        appFreqListView.currentIndex = index

                                        switch(type){
                                        case 1:

                                            appTextArea.text ="<b> Frequency : </b><i>"+frequency+" Mhz "
                                                    +"</i><br><b> QAM : </b><i>"+ qam +
                                                    "</i><br><b> SymbolRate : </b><i> "+symbolrate+" Msymbol/s"+
                                                    "</i><br><b> FEC_inner : </b><i> "+fec_inner+
                                                    "</i><br><b> FEC_outer : </b><i> "+fec_outer+"</i>"
                                            break;
                                        case 2:

                                            appTextArea.text ="<b> Frequency : </b><i>"+frequency+" Hz "
                                                    +"</i><br><b> Bandwidth : </b><i>"+ bandwidth +
                                                    "</i><br><b> Time_Slicing_indicator : </b><i> "+time_slicing_indicator+
                                                    "</i><br><b> MPE_FEC_indicator : </b><i> "+MPE_FEC_indicator+
                                                    "</i><br><b> constellation : </b><i> "+constellation+

                                                    "</i><br><b> hierarchy_information : </b><i> "+hierarchy_information+
                                                    "</i><br><b> Code_rate_HP_stream : </b><i> "+code_rate_HP_stream+
                                                    "</i><br><b> Code_rate_LP_stream : </b><i> "+code_rate_LP_stream+
                                                    "</i><br><b> guard_interval : </b><i> "+guard_interval+
                                                    "</i><br><b> transmission_mode : </b><i> "+transmission_mode+
                                                    "</i><br><b> other_frequency_flag : </b><i> "+other_frequency_flag+
                                                    "</i>"
                                            break;
                                        case 3:

                                            appTextArea.text ="<b> Frequency : </b><i>"+frequency+" Ghz "
                                                    +"</i><br><b> orbital_position : </b><i>"+orbital_position +"°"+
                                                    "</i><br><b> SymbolRate : </b><i> "+symbolrate+" Msymbol/s"+
                                                    "</i><br><b> FEC_inner : </b><i> "+fec_inner+
                                                    "</i><br><b> west_east_flag : </b><i> "+west_east_flag+
                                                    "</i><br><b> polarization : </b><i> "+polarization+
                                                    "</i><br><b> roll_offl : </b><i> "+roll_offl+
                                                    "</i><br><b> modulation_system : </b><i> "+modulation_system+
                                                    "</i><br><b> modulation_type : </b><i> "+modulation_type+"</i>"
                                            break;
                                        default:
                                            break;
                                        }

                                    }
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    id:rect2
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    anchors.margins: margin
                    radius: 5
                    ListView{
                        id:appChannelListView
                        //     Layout.fillWidth: true
                        //   Layout.fillHeight: true
                        orientation: Qt.Vertical
                        visible: true

                        width: ((appListLayout.width /2) - (margin*2))
                        height:  ((appListLayout.height) - (margin*2))
                        anchors.margins: margin

                        highlight: Rectangle{ color: "lightsteelblue" ;radius:5}
                        focus: true

                        model: tChannel
                        delegate: Component{
                            Item {
                                id:listElementChann
                                width: appChannelListView.width
                                height: 20
                                Column{
                                    Text {
                                        color: listElementChann.ListView.isCurrentItem ? "red" : "black"
                                        id:lstItem
                                        text: qsTr(cname)
                                    }
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        appChannelListView.currentIndex = index

                                        appTextArea.text = "<b> Chnnel name : </b><i>"+cname+
                                                //"</i><br><b> QAM : </b><i>"+qam+
                                                "</i><br><b> Frequency :  </b><i>"+frequency+
                                                // "</i><br><b> Symbol Rate :  </b><i>"+symbolrate+
                                                //  "</i><br><b> FEC_inner :  </b><i>"+fec_inner+
                                                // "</i><br><b> FEC_outer :  </b><i>"+fec_outer+
                                                "</i><br><b> ServiceID :  </b><i>"+progid+
                                                "</i><br><b> Audio PID :  </b><i>"+apid+
                                                "</i><br><b> Video PID :  </b><i> "+vpid+
                                                "</i><br><b> R PID :  </b><i> "+rpid+
                                                "</i><br><b> PMT PID :  </b><i> "+pmt+
                                                "</i><br><b> Audio Type :  </b><i> "+atype+
                                                "</i><br><b> Video Type :  </b><i> "+vtype+
                                                "</i><br><b> Sequence ID :  </b><i> "+sid+
                                                "</i><br><b> EPG Available :  </b><i> "+epg+
                                                "</i><br><b> Stream ID :  </b><i> "+streamid+
                                                "</i><br><b> Emcripted :  </b><i>  "+encrypted+
                                                "</i><br><b> Network ID :  </b><i> "+netwotkid+
                                                "</i><br><b> Language :  </b><i> "+lang+
                                                "</i><br><b> Channel state :  </b><i> "+s_state+
                                                "</i><br><b> Channel description :  </b><i> "+s_desc
                                    }
                                }

                                ///
                            }
                        }
                        ///
                    }
                }
            }
        }
        GroupBox{
            id:groupTwo
            title: qsTr("Description")
            Layout.fillWidth:  true
            Layout.fillHeight: true
            RowLayout{
                id:appTextLayout
                spacing: 10
                anchors.fill: parent
                //anchors.margins: margin
                TextArea{
                    id:appTextArea
                    anchors.fill: parent
                    readOnly: true
                    textFormat:TextEdit.RichText
                    text: "select frequency or channel list to see details "
                }
            }
        }
    }

    statusBar:StatusBar {
        id:appStatusBar
        RowLayout {
            anchors.fill: parent
            spacing: 10
            anchors.margins: margin
            Label {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "Ready..."
            }
            ProgressBar {
                Layout.fillWidth: true
                Layout.fillHeight: true
                value: 10
            }
        }
    }
    /*MouseArea {
        id: mouse_area1
        z: 1
        hoverEnabled: false
        anchors.fill: parent
        onClicked: {
            console.log("clicked")
        }
    }*/
    //        MainForm {
    //            anchors.fill: parent
    //            mouseArea.onClicked: {
    //               // console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
    //            }
    //        }
}
