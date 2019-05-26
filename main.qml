import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import "unit"
import "page"
Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Nox controller")

    Text {
        text: qsTr("Devices List")
        anchors.horizontalCenter: deviceList.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30
    }
    ListView{
        id: deviceList
        anchors.top: parent.top
        anchors.topMargin: 60
        model: AppModel.devicesList
        width: root.width/4
        height: parent.height - 60
        boundsBehavior: Flickable.StopAtBounds
        delegate: Item{
            width: parent.width
            height: 50
            Rectangle{
                width: parent.width
                height: 1
                anchors.top: parent.top
                color: "grey"
                visible: index == 0
            }
            Text {
                id: name
                text: modelData.instanceName
                anchors.centerIn: parent
            }
            Rectangle{
                width: parent.width
                height: 1
                anchors.bottom: parent.bottom
                color: "grey"
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    AppModel.requestToLaunchInstance(modelData.instanceName)
                }
            }
        }
    }

    Rectangle{
        id: line
        width: 2
        height: parent.height
        anchors.left: deviceList.right
        color: "black"
    }

    Item{
        id: contentArea
        width: parent.width - deviceList.width
        height: parent.height
        anchors.right: parent.right

        ComboBox {
            enabled: !AppModel.isLaunchMutiTask
            currentIndex: AppModel.amountOfThread - 1
            model: ListModel {
                id: cbItems
                ListElement { text: "1 Thread"}
                ListElement { text: "2 Threads"}
                ListElement { text: "3 Threads"}
                ListElement { text: "4 Threads"}
            }
            width: 200
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: startBtn.top
            anchors.bottomMargin: 20
            onActivated: {
                AppModel.amountOfThread = currentIndex + 1
            }
        }

        Button{
            id: startBtn
            anchors.centerIn: parent
            width: 100
            height: 50
            text: AppModel.isLaunchMutiTask? "Stop" : "Start"
            onClicked: AppModel.isLaunchMutiTask = !AppModel.isLaunchMutiTask
        }

    }

    Rectangle{
        anchors.fill: parent
        opacity: 0.5
        visible: AppModel.noxIntallFolder == ""
        MouseArea{
            anchors.fill: parent
            propagateComposedEvents: false
        }
    }

    SettingPage{
        id: settingPage
        x: parent.width
        y: 0
        width: parent.width
        height: parent.height
        onXChanged: {
            if(x == 0){
                isOpenned = true
            }else if(x == parent.width ){
                isOpenned = false
            }
        }
    }
    ButtonItem{
        id: settingBtn
        anchors.right: parent.right
        anchors.top: parent.top
        iconSource: "qrc:/setting.png"
        width: 50
        height: 50
        imgIcon.width: 30
        imgIcon.height: 30

        onButtonClicked: {
            settingPage.startAnimation()
        }
    }

    Component.onCompleted: {
        if(AppModel.noxIntallFolder == ""){
            settingPage.startAnimation()
        }
    }
}
