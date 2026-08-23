/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 * SPDX-License-Identifier: Apache-2.0
 */

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: root
    visible: true
    width: 1000
    height: 620
    minimumWidth: 800
    minimumHeight: 500
    title: qsTr("RT-Thread 控制台")

    Material.theme: Material.Dark
    Material.accent: "#53c7f5"
    Material.primary: "#172438"

    property bool serviceRunning: true
    property int cpuLoad: 38
    property int memoryLoad: 56
    property string lastEvent: qsTr("服务已就绪，等待操作")

    Timer {
        interval: 1600
        repeat: true
        running: true
        onTriggered: {
            if (root.serviceRunning) {
                root.cpuLoad = 30 + Math.floor(Math.random() * 30)
                root.memoryLoad = 51 + Math.floor(Math.random() * 13)
                root.lastEvent = qsTr("监测线程已更新")
            }
        }
    }

    header: ToolBar {
        height: 64
        background: Rectangle { color: "#172438" }

        Row {
            anchors.fill: parent
            anchors.leftMargin: 28
            anchors.rightMargin: 28
            spacing: 14

            Rectangle {
                width: 30; height: 30; radius: 8
                anchors.verticalCenter: parent.verticalCenter
                color: "#38c898"
                Text { anchors.centerIn: parent; text: "RT"; color: "#102116"; font.bold: true; font.pixelSize: 12 }
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 2
                Text { text: qsTr("RT-Thread 设备控制台"); color: "#f4f8ff"; font.pixelSize: 20; font.bold: true }
                Text { text: qsTr("Qt Quick · kernel mode"); color: "#9db2ce"; font.pixelSize: 12 }
            }

            Item { width: parent.width - 500; height: 1 }

            Rectangle {
                anchors.verticalCenter: parent.verticalCenter
                width: 106; height: 30; radius: 15
                color: root.serviceRunning ? "#1d5b4b" : "#5d3941"
                Row {
                    anchors.centerIn: parent
                    spacing: 7
                    Rectangle { width: 8; height: 8; radius: 4; anchors.verticalCenter: parent.verticalCenter; color: root.serviceRunning ? "#45e0a5" : "#ff8f9b" }
                    Text { anchors.verticalCenter: parent.verticalCenter; text: root.serviceRunning ? qsTr("运行中") : qsTr("已停止"); color: "#ffffff"; font.pixelSize: 13 }
                }
            }
        }
    }

    background: Rectangle { color: "#101827" }

    Item {
        anchors.fill: parent
        anchors.margins: 28

        Column {
            anchors.fill: parent
            spacing: 18

            Row {
                width: parent.width; height: 112; spacing: 18
                Repeater {
                    model: [
                        { "label": qsTr("系统状态"), "value": root.serviceRunning ? qsTr("正常") : qsTr("待机"), "detail": qsTr("所有核心在线"), "color": "#38c898" },
                        { "label": qsTr("网络连接"), "value": qsTr("已连接"), "detail": qsTr("virtio-net0"), "color": "#53c7f5" },
                        { "label": qsTr("运行时间"), "value": qsTr("00:12:48"), "detail": qsTr("QEMU virt RISC-V"), "color": "#a88cff" }
                    ]
                    Rectangle {
                        width: (parent.width - 36) / 3; height: parent.height; radius: 12
                        color: "#172438"; border.color: "#2a405f"
                        Rectangle { width: 5; anchors.left: parent.left; anchors.top: parent.top; anchors.bottom: parent.bottom; radius: 2; color: modelData.color }
                        Column {
                            anchors.fill: parent; anchors.leftMargin: 22; anchors.topMargin: 17; spacing: 6
                            Text { text: modelData.label; color: "#9db2ce"; font.pixelSize: 13 }
                            Text { text: modelData.value; color: "#f4f8ff"; font.pixelSize: 25; font.bold: true }
                            Text { text: modelData.detail; color: "#6f88a8"; font.pixelSize: 12 }
                        }
                    }
                }
            }

            Row {
                width: parent.width; height: 235; spacing: 18
                Rectangle {
                    id: monitorCard
                    width: parent.width * 0.61; height: parent.height; radius: 12
                    color: "#172438"; border.color: "#2a405f"
                    Column {
                        anchors.fill: parent; anchors.margins: 22; spacing: 18
                        Text { text: qsTr("资源监控"); color: "#f4f8ff"; font.pixelSize: 18; font.bold: true }
                        Column {
                            width: parent.width; spacing: 8
                            Row {
                                width: parent.width
                                Text { text: qsTr("CPU 使用率"); color: "#b9c9de"; font.pixelSize: 14 }
                                Item { width: parent.width - 178; height: 1 }
                                Text { text: root.cpuLoad + "%"; color: "#53c7f5"; font.pixelSize: 14; font.bold: true }
                            }
                            ProgressBar {
                                id: cpuProgress
                                width: parent.width; from: 0; to: 100; value: root.cpuLoad
                                background: Rectangle { implicitHeight: 10; radius: 5; color: "#0e1624" }
                                contentItem: Item { Rectangle { width: cpuProgress.visualPosition * parent.width; height: parent.height; radius: 5; color: "#53c7f5" } }
                            }
                        }
                        Column {
                            width: parent.width; spacing: 8
                            Row {
                                width: parent.width
                                Text { text: qsTr("内存使用率"); color: "#b9c9de"; font.pixelSize: 14 }
                                Item { width: parent.width - 190; height: 1 }
                                Text { text: root.memoryLoad + "%"; color: "#a88cff"; font.pixelSize: 14; font.bold: true }
                            }
                            ProgressBar {
                                id: memoryProgress
                                width: parent.width; from: 0; to: 100; value: root.memoryLoad
                                background: Rectangle { implicitHeight: 10; radius: 5; color: "#0e1624" }
                                contentItem: Item { Rectangle { width: memoryProgress.visualPosition * parent.width; height: parent.height; radius: 5; color: "#a88cff" } }
                            }
                        }
                        Text { text: qsTr("采样周期：1.6 秒  ·  CPU 0-3 在线"); color: "#6f88a8"; font.pixelSize: 12 }
                    }
                }

                Rectangle {
                    width: parent.width - monitorCard.width - 18; height: parent.height; radius: 12
                    color: "#172438"; border.color: "#2a405f"
                    Column {
                        anchors.fill: parent; anchors.margins: 22; spacing: 14
                        Text { text: qsTr("快捷操作"); color: "#f4f8ff"; font.pixelSize: 18; font.bold: true }
                        Text { text: root.lastEvent; color: "#9db2ce"; font.pixelSize: 13; wrapMode: Text.WordWrap; width: parent.width }
                        Button {
                            width: parent.width; text: root.serviceRunning ? qsTr("停止服务") : qsTr("启动服务"); highlighted: true
                            onClicked: { root.serviceRunning = !root.serviceRunning; root.lastEvent = root.serviceRunning ? qsTr("服务已启动") : qsTr("服务已停止"); console.log(root.lastEvent) }
                        }
                        Button { width: parent.width; text: qsTr("刷新设备状态"); onClicked: { root.lastEvent = qsTr("设备状态已刷新"); console.log(root.lastEvent) } }
                    }
                }
            }

            Rectangle {
                width: parent.width; height: parent.height - 383; radius: 12
                color: "#0c1320"; border.color: "#2a405f"
                Column {
                    anchors.fill: parent; anchors.margins: 18; spacing: 7
                    Text { text: qsTr("系统事件"); color: "#f4f8ff"; font.pixelSize: 16; font.bold: true }
                    Repeater {
                        model: [ qsTr("[info] virtio-gpu: framebuffer 已连接"), qsTr("[info] Qt Quick: software backend 已启用"), qsTr("[info] input: pointer device 已注册") ]
                        Text { text: modelData; color: "#77d5b3"; font.pixelSize: 12 }
                    }
                }
            }
        }
    }
}
