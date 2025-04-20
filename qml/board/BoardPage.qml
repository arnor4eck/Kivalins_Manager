import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import "../dto"
import "../task"

Page {
    id: root
    property color backgroundColor: "lightblue"
    property int textSize: 24
    property StackView stackView
    property string boardName: "Название доски"
    property int boardId: -1;

    Component.onCompleted: {
        taskModel.refreshModel(root.boardId)
    }


    background: Rectangle{
        id: backgroundRect
        color: root.backgroundColor
    }

    ColumnLayout{
        id: coColumn
        anchors.fill: parent
        spacing: 5

        Rectangle{
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.fillWidth: true
            height: back.height
            color: root.backgroundColor
            CustomButton{
                id: back
                text: "<"
                textSize: root.textSize
                needsPadding: false
                radius: 0
                onClicked: {
                    stackView.pop()
                }
            }
            Text{
                id: name
                anchors.centerIn: parent
                text: boardName
                font.pixelSize: root.textSize
                font.weight: Font.DemiBold
            }
        }

        CreateTaskWindow{
            id: createTaskWindow
            textSize: root.textSize
            boardId: root.boardId
        }

        RowLayout{
            id: coRow
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 5

            ColumnLayout{
                id: innerButtonColumn
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                spacing: 5
                CustomButton{
                    id: createTaskButton
                    text: "Создать задачу"
                    textSize: root.textSize
                    Layout.fillWidth: true
                    onClicked: {
                        createTaskWindow.open();
                    }
                }

                StatisticsWindow{
                    id: statWindow
                    textSize: root.textSize
                    boardId: root.boardId
                }

                CustomButton{
                    id: statistics
                    text: "Статистика"
                    textSize: root.textSize
                    buttonColor: "darkgreen"
                    textColor: "lightgreen"
                    Layout.fillWidth: true
                    width: innerButtonColumn.width

                    onClicked: {
                        statWindow.createdTasks = taskModel.getCreatedCount(root.boardId)
                        statWindow.doneTasks = taskModel.getDoneCount(root.boardId)
                        statWindow.open();
                    }
                }
                CustomButton{
                    id: types
                    text: "Типы задач"
                    textSize: root.textSize
                    Layout.fillWidth: true
                    width: innerButtonColumn.width
                    onClicked: {
                        stackView.push("../type/TypesBoard.qml", {
                            textSize: root.textSize,
                            stackView: root.stackView,
                            boardId: root.boardId
                        })
                    }
                }

                FilterTasksWindow{
                    id: filterTasksWindow
                    textSize: root.textSize;
                    parentWidth: root.width;
                    parentHeight: root.height;
                    boardId: root.boardId;
                }

                CustomButton{
                    id: filter
                    text: "Фильтр"
                    textSize: root.textSize
                    Layout.fillWidth: true
                    width: innerButtonColumn.width
                    buttonColor: "darkgreen"
                    textColor: "lightgreen"
                    onClicked: {
                        filterTasksWindow.open();
                    }
                }

                SuccessWindow{
                    id: success
                    textSize: root.textSize
                }

                ErrorWindow{
                    textSize: root.textSize
                    id: error
                }

                Connections {
                    target: boardModel
                    function onShowError(message) {
                        error.errorText = message;
                        error.textSize = root.textSize
                        error.open();
                    }
                }

                FileDialog {
                    id: fileDialog
                    title: "Проводник"
                    fileMode: FileDialog.SaveFile
                    nameFilters: ["Табличные данные (*.csv)"]
                    defaultSuffix: "csv"

                    onAccepted: {
                        boardModel.exportBoard(selectedFile, root.boardId);
                        success.text = "Данные экспортированы!";
                        success.open();
                    }
                }

                CustomButton{
                    id: exportExcel
                    text: "Экспорт"
                    textSize: root.textSize
                    Layout.fillWidth: true
                    width: innerButtonColumn.width
                    onClicked: {
                        fileDialog.open();
                    }
                }
            }

            Rectangle{
                Layout.alignment: Qt.AlignLeft
                Layout.fillHeight: true
                width: 1
                color: "black"
            }

            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                contentWidth: availableWidth

                ColumnLayout {
                    id: tasks
                    width: parent.width
                    spacing: 5

                    Repeater {
                        model: taskModel
                        delegate: TaskIcon {
                            Layout.fillWidth: true
                            Layout.preferredWidth: tasks.width
                            textSize: root.textSize
                            taskName: model.name;
                            description: model.description;
                            creationTime: model.creationTime;
                            taskType: model.type;
                            taskId: model.id;
                            boardId: root.boardId
                        }
                    }
                }
            }
            Rectangle{
                Layout.alignment: Qt.AlignLeft
                Layout.fillHeight: true
                width: 1
                color: "black"
            }
        }

        Item{
            Layout.fillHeight: true
        }
    }
}
