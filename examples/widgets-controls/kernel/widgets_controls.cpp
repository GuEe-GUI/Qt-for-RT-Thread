/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <QApplication>
#include <QCheckBox>
#include <QDebug>
#include <QFontDatabase>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QProgressBar>
#include <QProxyStyle>
#include <QPushButton>
#include <QRadioButton>
#include <QStyleOption>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

class ControlIndicatorStyle final : public QProxyStyle
{
public:
    explicit ControlIndicatorStyle(QStyle *baseStyle) : QProxyStyle(baseStyle) {}

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                       QPainter *painter, const QWidget *widget = nullptr) const override
    {
        if (element != PE_IndicatorCheckBox && element != PE_IndicatorRadioButton)
        {
            QProxyStyle::drawPrimitive(element, option, painter, widget);
            return;
        }

        const bool enabled = option->state & State_Enabled;
        const bool checked = option->state & State_On;
        const QRectF box = option->rect.adjusted(1, 1, -1, -1);
        const QColor border = enabled ? QColor("#7f9ab9") : QColor("#526277");
        const QColor fill = checked ? QColor("#40c98a") : QColor("#172338");

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(QPen(border, 1.5));
        painter->setBrush(fill);

        if (element == PE_IndicatorRadioButton)
        {
            painter->drawEllipse(box);
            if (checked)
            {
                painter->setPen(Qt::NoPen);
                painter->setBrush(QColor("#10291f"));
                painter->drawEllipse(box.adjusted(4, 4, -4, -4));
            }
        }
        else
        {
            painter->drawRoundedRect(box, 3, 3);
            if (checked)
            {
                painter->setPen(QPen(QColor("#10291f"), 2.2, Qt::SolidLine,
                                     Qt::RoundCap, Qt::RoundJoin));
                painter->drawLine(QPointF(box.left() + 3.5, box.center().y()),
                                  QPointF(box.center().x() - 0.5, box.bottom() - 3.5));
                painter->drawLine(QPointF(box.center().x() - 0.5, box.bottom() - 3.5),
                                  QPointF(box.right() - 3, box.top() + 3.5));
            }
        }
        painter->restore();
    }
};

static int widgets_controls_main()
{
    int argc = 1;
    char application_name[] = "qt-widgets-controls";
    char *argv[] = {application_name, nullptr};

    if (!qgetenv("QT_SCALE_FACTOR").isEmpty())
    {
        QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    }

    QApplication app(argc, argv);
    app.setStyle(new ControlIndicatorStyle(app.style()));

    const int font_id = QFontDatabase::addApplicationFont("/fonts/wqy-microhei.ttc");
    if (font_id >= 0)
    {
        const QString family = QFontDatabase::applicationFontFamilies(font_id).at(0);
        QApplication::setFont(QFont(family));
        qDebug() << "Loaded font families:" << QFontDatabase::applicationFontFamilies(font_id);
    }
    else
    {
        qWarning() << "Failed to load application font.";
    }

    QWidget window;
    window.setWindowTitle("RT-Thread Qt 控件演示");
    window.resize(800, 600);
    window.setStyleSheet(
        "QWidget { background: #202b3b; color: #e8f1ff; }"
        "QGroupBox { border: 1px solid #4a6689; border-radius: 8px; "
        " margin-top: 12px; padding: 12px; font-weight: bold; }"
        "QGroupBox::title { subcontrol-origin: margin; left: 14px; padding: 0 6px; "
        " color: #84d9b0; }"
        "QCheckBox, QRadioButton { spacing: 8px; padding: 3px; }"
        "QCheckBox:disabled, QRadioButton:disabled { color: #7d8ba0; }"
        "QLineEdit { background: #142033; border: 1px solid #55769b; border-radius: 6px; "
        " padding: 7px; selection-background-color: #3bbf7a; }"
        "QPushButton { background: #2fb873; border: 0; border-radius: 8px; "
        " padding: 9px 18px; color: #10281e; font-weight: bold; }"
        "QPushButton:pressed { background: #8de4b7; }"
        "QProgressBar { border: 1px solid #55769b; border-radius: 6px; text-align: center; "
        " background: #142033; }"
        "QProgressBar::chunk { background: #3bc987; border-radius: 5px; }"
        "QMenu { background: #101926; color: #edf5ff; border: 1px solid #7594b8; "
        " border-radius: 7px; padding: 6px; }"
        "QMenu::item { background: transparent; border-radius: 4px; padding: 7px 28px 7px 12px; "
        " margin: 2px 3px; }"
        "QMenu::item:selected { background: #42c98c; color: #10291f; }"
        "QMenu::item:disabled { color: #738299; }"
        "QMenu::separator { height: 1px; background: #4d6685; margin: 5px 8px; }");

    QVBoxLayout main_layout(&window);

    QLabel title("Qt 控件渲染预览");
    title.setAlignment(Qt::AlignCenter);
    title.setStyleSheet("font-weight: bold; font-size: 20px;");
    main_layout.addWidget(&title);

    QGroupBox status_box("控件状态示例");
    QVBoxLayout status_layout(&status_box);
    QCheckBox checked_box("选中状态");
    checked_box.setChecked(true);
    QCheckBox unchecked_box("未选中状态");
    QCheckBox disabled_box("不可用状态");
    disabled_box.setEnabled(false);
    disabled_box.setChecked(true);
    QRadioButton selected_radio("单选 A（选中）");
    selected_radio.setChecked(true);
    QRadioButton radio("单选 B");
    status_layout.addWidget(&checked_box);
    status_layout.addWidget(&unchecked_box);
    status_layout.addWidget(&disabled_box);
    status_layout.addWidget(&selected_radio);
    status_layout.addWidget(&radio);
    main_layout.addWidget(&status_box);

    QLabel font_label("字体渲染测试：");
    main_layout.addWidget(&font_label);
    QLabel font_preview("ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n1234567890!@#$%^&*()");
    font_preview.setAlignment(Qt::AlignCenter);
    font_preview.setStyleSheet("font-size: 14px;");
    main_layout.addWidget(&font_preview);

    QGroupBox progress_box("自动更新的进度条");
    QVBoxLayout progress_layout(&progress_box);
    QProgressBar progress_bar;
    progress_bar.setRange(0, 100);
    progress_layout.addWidget(&progress_bar);
    main_layout.addWidget(&progress_box);

    QTimer timer(&window);
    QObject::connect(&timer, &QTimer::timeout, [&progress_bar]() {
        progress_bar.setValue((progress_bar.value() + 5) % 101);
    });
    timer.start(500);

    QLineEdit line_edit;
    line_edit.setPlaceholderText("输入内容");
    main_layout.addWidget(&line_edit);

    QPushButton click_button("点击测试按钮");
    main_layout.addWidget(&click_button);
    QObject::connect(&click_button, &QPushButton::clicked, [&click_button]() {
        static int count = 1;
        click_button.setText("已点击 " + QString::number(count++) + " 次");
    });

    window.show();
    return app.exec();
}

extern "C" void qt_main(void *parameter)
{
    Q_UNUSED(parameter);
    widgets_controls_main();
}
