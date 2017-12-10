import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

Rectangle {
    id: rectangle
    property alias mouseArea: mouseArea

    width: 360
    height: 360
    property alias toolButton: toolButton

    MouseArea {
        id: mouseArea
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        ToolBar {
            id: toolBar
            y: 0
            width: 360
            anchors.left: parent.left
            anchors.leftMargin: 0

            ToolButton {
                id: toolButton
                y: 0
                width: 55
                height: 30
                text: qsTr("Open")
                spacing: 5
                highlighted: false
                anchors.left: parent.left
                anchors.leftMargin: 9
            }
        }

        RowLayout {
            x: 185
            y: 343
            anchors.horizontalCenter: toolBar.horizontalCenter

            Text {
                id: text3
                text: qsTr("Text")
                Layout.fillWidth: true
                font.pixelSize: 12
            }

            ProgressBar {
                id: progressBar
                Layout.fillWidth: false
                value: 0.5
            }
        }

        RowLayout {
            x: 10
            y: 219
            width: 305
            height: 121
            anchors.horizontalCenterOffset: 0
            clip: false
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                id: text2
                width: 173
                text: qsTr("Text")
                wrapMode: Text.WordWrap
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: 12
            }

            Text {
                id: text1
                x: 100
                width: 223
                text: qsTr("Text")
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                wrapMode: Text.WordWrap
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 121
                Layout.preferredWidth: 168
                font.pixelSize: 12
            }
        }

        RowLayout {
            x: 10
            y: 53
            anchors.horizontalCenter: parent.horizontalCenter

            ListView {
                id: listView
                Layout.fillHeight: false
                Layout.fillWidth: true
                Layout.preferredHeight: 160
                Layout.preferredWidth: 110
                delegate: Item {
                    x: 5
                    width: 80
                    height: 40
                    Row {
                        id: row1
                        Rectangle {
                            width: 40
                            height: 40
                            color: colorCode
                        }

                        Text {
                            text: name
                            font.bold: true
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        spacing: 10
                    }
                }
                model: ListModel {
                    ListElement {
                        name: "Grey"
                        colorCode: "grey"
                    }

                    ListElement {
                        name: "Red"
                        colorCode: "red"
                    }

                    ListElement {
                        name: "Blue"
                        colorCode: "blue"
                    }

                    ListElement {
                        name: "Green"
                        colorCode: "green"
                    }
                }
            }

            ListView {
                id: listView1
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 160
                Layout.preferredWidth: 110
                delegate: Item {
                    x: 5
                    width: 80
                    height: 40
                    Row {
                        id: row2
                        Rectangle {
                            width: 40
                            height: 40
                            color: colorCode
                        }

                        Text {
                            text: name
                            font.bold: true
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        spacing: 10
                    }
                }
                model: ListModel {
                    ListElement {
                        name: "Grey"
                        colorCode: "grey"
                    }

                    ListElement {
                        name: "Red"
                        colorCode: "red"
                    }

                    ListElement {
                        name: "Blue"
                        colorCode: "blue"
                    }

                    ListElement {
                        name: "Green"
                        colorCode: "green"
                    }
                }
            }
        }
    }
}
