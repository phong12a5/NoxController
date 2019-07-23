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

    /* --------------- functions -------------- */
    function getThreadsModel(list){
        var data = []
        for(var j = 0; j < AppModel.maxNumberThread; j++){
            data.push(j + 1 + "Thread")
        }
        return data
    }

    Text {
        text: qsTr("Devices List")
        anchors.horizontalCenter: deviceList.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30
        font.pixelSize: 20
    }
    ListView{
        id: deviceList
        anchors.top: parent.top
        anchors.topMargin: 60
        model: AppModel.devicesList
        width: root.width/4
        height: parent.height - 60
        boundsBehavior: Flickable.StopAtBounds
        clip: true
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

        Item {
            id: tokenItem
            height: 50
            width: title.width + token.width
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 50

            Text {
                id: title
                text: qsTr("Token: ")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 15
            }

            TextField {
                id: token
                text: AppModel.token
                font.pixelSize: 15
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                onTextChanged: AppModel.token = text
            }
        }

        ComboBox {
            enabled: !AppModel.isLaunchMutiTask
            currentIndex: AppModel.amountOfThread - 1
            model: getThreadsModel(AppModel.devicesList)
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

            property bool selected: false
            anchors.centerIn: parent
            width: 100
            height: 50
            text: selected? "Stop" : "Start"
            onClicked: {
                selected = !selected
                if(selected){
                    AppModel.initializing = true
                    AppModel.startProgram()
                }
                else
                    AppModel.stopProgarm()
            }
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
        iconSource: "qrc:/image/setting.png"
        width: 50
        height: 50
        imgIcon.width: 30
        imgIcon.height: 30

        onButtonClicked: {
            settingPage.startAnimation()
        }
    }

    Rectangle{
        id: initPopup
        anchors.fill: parent
        color: "black"
        opacity: 0.8
        visible: AppModel.initializing
    }

    Text {
        text: qsTr("Initializing devices ........\nAnyway, Don't turn off application!")
        color: "white"
        anchors.centerIn: initPopup
        font.pixelSize: 15
        visible: AppModel.initializing
        horizontalAlignment: Text.AlignHCenter
    }

    Component.onCompleted: {
        if(AppModel.noxIntallFolder == ""){
            settingPage.startAnimation()
        }
    }
}
