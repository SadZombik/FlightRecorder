#include "controlwidget.h"

ControlWidget::ControlWidget(quint16 width, quint16 height)
    : w(width), h(height)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    setFixedSize(w, h);

    layout = new QVBoxLayout(this);
    setLayout(layout);

    cb = new QComboBox(this);
    cb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    btn = new QPushButton;
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

ControlWidget::~ControlWidget()
{
    delete layout;
    delete cb;
}

QList<QString> ControlWidget::selected_list;

void ControlWidget::set_index(int index)
{
    cw_index = index;
}

AddWidget::AddWidget(quint16 width, quint16 height)
    : ControlWidget(width, height)
{
    setWindowTitle(__FUNCTION__);
    parse();

    cb->addItems(QStringList(name_list));
    connect(cb, SIGNAL(activated(int)), this, SLOT(set_index(int)));

    sub_plot = new QComboBox(this);

    for (int i = 0; i < 10; i++)
        sub_plot->addItem(QString::number(i));
    connect(sub_plot, SIGNAL(activated(int)), this, SLOT(set_sub_plot_index(int)));

    btn->setText("Добавить параметр");
    connect(btn, SIGNAL(clicked()), this, SLOT(add_param()));

    name_label.setText("Название параметра");
    min_label.setText("Минимальное значение");
    max_label.setText("Максимальное значение");
    subplot_label.setText("Номер подграфика");
    rad_to_deg_cb.setText("Радианы в градусы");

    min_edit.setRange(-10000, 10000);
    max_edit.setRange(-10000, 10000);
    min_edit.setValue(0);
    max_edit.setValue(100);

    layout->addWidget(&name_label);
    layout->addWidget(cb);
    layout->addWidget(&subplot_label);
    layout->addWidget(sub_plot);
    layout->addWidget(&min_label);
    layout->addWidget(&min_edit);
    layout->addWidget(&max_label);
    layout->addWidget(&max_edit);
    layout->addWidget(&rad_to_deg_cb);
    layout->addWidget(btn);
}

AddWidget::~AddWidget()
{
    delete sub_plot;
}

void AddWidget::add_param()
{
    selected_list.push_back(abbrevation_list[cw_index]);
    min_edit.setValue(0);
    max_edit.setValue(100);
    emit ready_add();
}

void AddWidget::set_sub_plot_index(int index)
{
    sub_plot_index = index;
}

void AddWidget::parse()
{
    // Сгенерировано StructReader.py
    name_list.push_back("Time; // время моделирования [сек]");
    name_list.push_back("dt; // квант времени моделирования [сек]");
    name_list.push_back("Hgeo; // геометрическая высота");
    name_list.push_back("Hbar; // высота барометрическая [м] \n [-1000, 10000]");
    name_list.push_back("Par005; // dТ,С [град], изменение \n температуры воздуха");
    name_list.push_back("Par006; // dр [мм.рт.ст.], изменение \n давления от МСА");
    name_list.push_back("windWx; // горизонтальная составляющая скорости ветра");
    name_list.push_back("windWy; // вертикальная составляющая скорости ветра");
    name_list.push_back("windWYaw; // азимут ветра");
    name_list.push_back("Vx; // скорость начала СвСК \n по Х м/с");
    name_list.push_back("Vy; // скорость начала СвСК \n по Y м/с");
    name_list.push_back("Vz; // скорость начала СвСК \n по Z м/с");
    name_list.push_back("Wx; // угловая скорость [рад/сек][-90:+90]");
    name_list.push_back("Wy; // угловая скорость [рад/сек][-90:+90]");
    name_list.push_back("Wz; // угловая скорость [рад/сек][-90:+90]");
    name_list.push_back("Yaw; // Psi угол рыскания [рад]");
    name_list.push_back("Pitch; // Tet угол тангажа [рад]");
    name_list.push_back("Roll; // Gam угол крена [рад]");
    name_list.push_back("Xg; // Xg [м], положенеи \n начала СвСК отноительно ЗСК (ГСК)");
    name_list.push_back("Yg; // Yg [м]");
    name_list.push_back("Zg; // Zg [м]");
    name_list.push_back("G; // текущая масса вертолета[кг]");
    name_list.push_back("dG; // изменение массы вертолета; //");
    name_list.push_back("Xct; // Хцт [м], текущая \n координата ц.м. в СвСК");
    name_list.push_back("Yct; // Yцт [м], текущая \n координата ц.м. в СвСК");
    name_list.push_back("Zct; // Zцт [м], текущая \n координата ц.м. в СвСК");
    name_list.push_back("dXct; // приращение центра вертолета \n Par027; //");
    name_list.push_back("dYct; // приращение центра вертолета \n Par028; //");
    name_list.push_back("dZct; // приращение центра вертолета \n Par029; //");
    name_list.push_back("Xv; // положение РУВ продольное \n [мм] [-200,200]");
    name_list.push_back("Xp; // положение РУВ поперечное \n [мм] [-200,200]");
    name_list.push_back("Xn; // положение педалей [мм] [-200,200]");
    name_list.push_back("Xosh; // Хош [мм], положение \n штока общего шага");
    name_list.push_back("Wnv; // угловая скорость несущего \n винта [рад/сек], [0,30]");
    name_list.push_back("Nx; // перегрузка продольная [-10:+10]");
    name_list.push_back("Ny; // перегрузка нормальная [-10:+10]");
    name_list.push_back("Nz; // перегрузка поперечная [-10:+10]");
    name_list.push_back("Vk; //Vk [м/сек], воздушная скорость \n вертолета (с учетом ветра)");
    name_list.push_back("RPMnv; //Par039 обороты несущего винта \n [%], [50,130]");
    name_list.push_back("Par040; // L0 операторы Родрига-Гамильтона");
    name_list.push_back("Par041; // L1");
    name_list.push_back("Par042; // L2");
    name_list.push_back("Par043; // L3");
    name_list.push_back("Vpr; // Vпр [м/сек], приборная \n скорость вертолета (с учетом ветра)");
    name_list.push_back("Par045; // dGт [кг], расход \n топлива за шаг интегрирования");
    name_list.push_back("Ax; // Par046; // Ax, \n ускорение продольное в СвСК [м/с2]");
    name_list.push_back("Ay; // Par047; // Ay, \n ускорение нормальное в СвСК");
    name_list.push_back("Az; // Par048; // Az, \n ускорение поперечное в СвСК");
    name_list.push_back("Par049; // [н*м], потребный крутящий \n момент несущей системы, >0 - требу");
    name_list.push_back("Par050; // [н*м/сек], потребная мощность \n несущей системы, >0 - требуетс");
    name_list.push_back("Alpha; // угол атаки [-180,180]");
    name_list.push_back("Beta; // угол скольжения [-180,180]");
    name_list.push_back("AlphaNV; // эквивалентный угол атаки \n несущего витнта [град], [-90,90]");
    name_list.push_back("Par054; // Ct, коэфф. тяги НВ");
    name_list.push_back("Par055; // mk, коэфф. крутящего \n момента НВ");
    name_list.push_back("A0; // коэффициент махового движения \n А0 [-10,10]");
    name_list.push_back("A1; // коэффициент махового движения \n А1 [-10,10]");
    name_list.push_back("B1; // коэффициент махового движения \n В1 [-10,10]");
    name_list.push_back("Par059; // Tet1 [град], управление \n по углу циклического шага на азим. л");
    name_list.push_back("Par060; // Tet2 [град], управление \n по углу циклического шага на азим. л");
    name_list.push_back("Par061; // Fош [град], угол \n общего шага НВ");
    name_list.push_back("AlphaRV; // эквивалентный угол атаки \n РВ [град], [-20,20]");
    name_list.push_back("Par063; // Ct, коэфф. тяги РВ");
    name_list.push_back("Par064; // mk, коэфф. крутящего \n момента РВ");
    name_list.push_back("Par065; // a0, коэфф. махового \n движения лопасти РВ");
    name_list.push_back("Par066; // a1");
    name_list.push_back("Par067; // b1");
    name_list.push_back("Par068; // Tet1 [град], управление \n по углу циклического шага на азим. л");
    name_list.push_back("Par069; // Tet2 [град], управление \n по углу циклического шага на азим. л");
    name_list.push_back("Par070; // Fош [град], угол \n общего шага РВ");
    name_list.push_back("Par071; // значения Vx*, [м/с2] \n + Связанная");
    name_list.push_back("Par072; // Vy*, [м/с2] +");
    name_list.push_back("Par073; // правых Vz*, [м/с2] \n + система");
    name_list.push_back("Par074; // Omx*, [рад/с2] +");
    name_list.push_back("Par075; // частей Omy*, [рад/с2] \n + координат");
    name_list.push_back("Par076; // Omz*, [рад/с2] +");
    name_list.push_back("Par077; // ДУ Omnv*, [рад/с2] \n углов. скор. винта относительно оси винта");
    name_list.push_back("Par078; // Xg*, [м/c] Земная");
    name_list.push_back("Par079; // Yg*, [м/c] система");
    name_list.push_back("Par080; // Zg*, [м/c] координат");
    name_list.push_back("Par081; // L0* Операторы");
    name_list.push_back("Par082; // L1* Родрига-Гамильтона");
    name_list.push_back("Par083; // L2* для определения");
    name_list.push_back("Par084; // L3* углов Эйлера");
    name_list.push_back("Par085; // Gт*, [кг/c] расход \n топлива за шаг интегрирования");
    name_list.push_back("Capa; // Наклон АП продольный [рад]");
    name_list.push_back("Zeta; // Наклон АП поперечный [рад]");
    name_list.push_back("Fosh; // общий шаг НВ \n [рад], [0,20]");
    name_list.push_back("Foshrv; // Fош [рад], углу \n общего шага РВ");
    name_list.push_back("Par090; // Nnv [об./мин], обороты \n НВ not used ???? 190.");
    name_list.push_back("Roh; // плотность воздуха, [кг/м3]");
    name_list.push_back("Ph; // давление воздуха, [мм.рт.ст.] \n - показания на шкале высотомера");
    name_list.push_back("Th; // температура воздуха, [град, C]");
    name_list.push_back("Ah; // скорость звука, [м/сек]");
    name_list.push_back("Par095; // вертикальная скорость в \n ЗСК, [м/сек]");
    name_list.push_back("Par096_Xb; // Хвдж [ед], положение \n джойстика в продольном канале 0-255");
    name_list.push_back("Par097_Xk; // Хkдж [ед], положение \n джойстика в поперечном канале 0-255");
    name_list.push_back("Par098_Xp; // Хндж [ед], положение \n джойстика педалей 0-255");
    name_list.push_back("Par099_Fosh; // Хошдж [ед], положение \n джойстика общего шага 0-255");
    name_list.push_back("Par100_Ecor; // Хкддж [ед], положение \n джойстика левой-правой коррекции двигателя 0-255");
    name_list.push_back("Par101; // размерные силы - \n аэродин., инерционные, внешние [н]");
    name_list.push_back("Par102; //");
    name_list.push_back("Par103; //");
    name_list.push_back("Par104; // размерные моменты - \n аэродин., кориолиса, инерционные, внешни");
    name_list.push_back("Par105; //");
    name_list.push_back("Par106; //");
    name_list.push_back("Par107; // размерные силы реакций \n шасси в СвСК [н]");
    name_list.push_back("Par108; //");
    name_list.push_back("Par109; //");
    name_list.push_back("Par110; // размерные моменты от \n реакций шасси относ. ц.м. [н*м]");
    name_list.push_back("Par111; //");
    name_list.push_back("Par112; //");
    name_list.push_back("Par113; // размерные силы внешнего \n воздействия в СвСК [н]");
    name_list.push_back("Par114; //");
    name_list.push_back("Par115; //");
    name_list.push_back("Par116; // размерные моменты внешнего \n воздействия относ. ц.м. [н*м]");
    name_list.push_back("Par117; //");
    name_list.push_back("Par118; //");
    name_list.push_back("Par119; // суммарный момент инерции \n отосительно ц.м. [кг*м2]");
    name_list.push_back("Par120; //");
    name_list.push_back("Par121; //");
    name_list.push_back("Par122; //");
    name_list.push_back("Par123; //");
    name_list.push_back("Par124; //");
    name_list.push_back("Par125; // [кВт] - мощность \n левого двигателя");
    name_list.push_back("Par126; // [кВт] - правого");
    name_list.push_back("Par127; // [кг*м] - крутящий \n момент левого двигателя");
    name_list.push_back("Par128; // [кг*м] - правого");
    name_list.push_back("Par129; // продольный");
    name_list.push_back("Par130; // поперечный");
    name_list.push_back("Par131; // Wвх [м/с], компоненты \n вектора скорости");
    name_list.push_back("Par132; // Wвy ветра в СвСК");
    name_list.push_back("Par133; // Wвz");
    name_list.push_back("Par134; // Capa [рад], углы отклонения");
    name_list.push_back("Par135; // Zeta управляющих поверхностей");
    name_list.push_back("Par136; // Fош для i+1 \n шага расчета");
    name_list.push_back("Par137; // Fрв для корректировки \n по градиенту управления");
    name_list.push_back("Par138; // Zeta [рад], отклонение \n АП - поперечный канал");
    name_list.push_back("Par139; // Capa отклонение АП \n - продольный канал");
    name_list.push_back("Par140; // Fochrv отклонение ОШ \n РВ - канал курса");
    name_list.push_back("Par141; // Fochnv отклонение ОШ \n НВ - канал высоты");
    name_list.push_back("Par142; // тяга НВ [н]");
    name_list.push_back("Par143; // тяга РВ [н]");
    name_list.push_back("Par144; // располагаемая мощность СУ [н*м/сек=ватт]");
    name_list.push_back("Par145; // управление тормозом 0 \n - 255");
    name_list.push_back("Par146; // TRIM1 [ед], полож. \n РРУ левого (0-255) - МГ - от себя - 0");
    name_list.push_back("Par147; // TRIM2 [ед], полож. \n РРУ правого двигателя (0-255) - МГ - влево - 0");
    name_list.push_back("Par148; // шарик на АГ�� \n D_ball >0 - шарик отклоняется вправо");
    name_list.push_back("Par149; // [н*м/сек], потребная мощность \n НВ, >0 - требуется подводить внешнюю мощность");
    name_list.push_back("Par150; // [н*м/сек], потребная мощность \n РВ, >0 - требуется подводить внешнюю мощность");
    name_list.push_back("Par151; // Press_surf [кг/см2] - \n прочность грунта ВПП [5...9,5] 0 = бетонная ВПП");
    name_list.push_back("Par152; // Nтк, обороты двигателя \n 1 Left %");
    name_list.push_back("Par153; // Nтк, обороты двигателя \n 2 Right %");
    name_list.push_back("Par154; // Тг, температура газов \n левого двигателя [С, град]");
    name_list.push_back("Par155; // Тг, температура газов \n правого двигателя [С, град]");
    name_list.push_back("Par156; // Xg [м], положение \n ц.м. внешней подвески в ЗСК (ГСК)");
    name_list.push_back("Par157; // Yg [м]");
    name_list.push_back("Par158; // Zg [м]");
    name_list.push_back("Par159; // [л], количество (остаток) \n топлива. в зависимости от положения переключателя контроля топлива Iinput(30)");
    name_list.push_back("Par160; // [кг/см2], давление масла \n Рм левого двигателя");
    name_list.push_back("Par161; // [кг/см2], давление масла \n Рм правого двигателя");
    name_list.push_back("Par162; // [С, град], температура \n масла Тм левого двигателя");
    name_list.push_back("Par163; // [С, град], температура \n масла Тм правого двигателя");
    name_list.push_back("Par164; // [-1...0...1], по направлению, \n лимб влево-центр-вправо");
    name_list.push_back("Par165; // [-1...0...1], по крену, \n лимб левый край вверх-горизонт-правый край вверх");
    name_list.push_back("Par166; // [-1...0...1], по тангажу, \n лимб вниз-центр-вверх");
    name_list.push_back("Par167; // [-1...0...1], по высоте, \n лимб вниз-центр-вверх");
    name_list.push_back("Par168; // [л], топливо в \n топливных баках");
    name_list.push_back("Par169; // [град], указатель ДИСС \n - угол сноса");
    name_list.push_back("Par170; // [ед.], безразмерная располагаемая \n мощность двигателя, 0...1");
    name_list.push_back("Par171; // [ед.], реальная мощность \n левого двигателя, 0...1");
    name_list.push_back("Par172; // [ед.], реальная мощность \n правого двигателя, 0...1");
    name_list.push_back("Par173; // [м/с], указатель ДИСС \n - продольная (путевая) скорость Vx (траекторная СК)");
    name_list.push_back("Par174; // [м/с], указатель ДИСС \n - боковая скорость Vz (скорость сноса СвСК и ТрСК)");
    name_list.push_back("Par175; // Тм, температура масла \n главного редуктора [С, град]");
    name_list.push_back("Par176; // [кг/см2], давление масла \n Рм главного редуктора");
    name_list.push_back("Par177; // Тм, температура масла \n промежуточного редуктора [С, град]");
    name_list.push_back("Par178; // Тм, температура масла \n хвостового редуктора [С, град]");
    name_list.push_back("Par179; // [-1...0...1], при уменьшении \n давления и повышении температуры - отклонение влево");
    name_list.push_back("Par180; // Gam [рад], крен \n дублирующего прибора, указателя разворота");
    name_list.push_back("Par181; // [км], координата Х");
    name_list.push_back("Par182; // [км], координата Z");
    name_list.push_back("Par183; // [рад], угол между \n продольной осью вертолета и направлением на радиомаяк в ЗСК");
    name_list.push_back("Par184; // [км], координата Х");
    name_list.push_back("Par185; // [км], координата Z");
    name_list.push_back("Par186; // [рад], угол между \n продольной осью вертолета и направлением на радиомаяк в ЗСК");
    name_list.push_back("Par187; // Vxg [м/с], скорость \n ц.м. внешней подвески в ЗСК (ГСК)");
    name_list.push_back("Par188; // Vyg [м/с], скорость \n ц.м. внешней подвески в ЗСК (ГСК)");
    name_list.push_back("Par189; // Vzg [м/с], скорость \n ц.м. внешней подвески в ЗСК (ГСК)");
    name_list.push_back("Par190; // [мм.рт.ст.], текущее значение \n барометрического давления Ph/133.3 задается при старте?");
    name_list.push_back("Par191; // [мм.рт.ст.], заданное барометрическое \n давление для t=0 (перед взлетом) ?");
    name_list.push_back("Par192; // давление воздуха, [мм.рт.ст.] \n (аналог R92) - показания на шкале высотомера");
    name_list.push_back("Par193; // Нбар [м], (аналог \n R4) - по начальному давлению на взлете и изменению высоты");
    name_list.push_back("Par194; // общий шаг");
    name_list.push_back("Par195; // шаг рулевого винта");
    name_list.push_back("Par196; // [м/с], сред. квад. \n скорость возмущенного ветра в ГСК (для R7)");
    name_list.push_back("Par197; // [м/с], сред. квад. \n скорость вертикального порыва ветра в ГСК (для R8)");
    name_list.push_back("Par198; // [м/с], скорость по \n ДИСС (траекторная СК) Routput(198)=Sqrt(DICC_Vx**2+DICC_Vz**2)");
    name_list.push_back("Par199; //");
    name_list.push_back("Par200; // [м], геометрическая высота \n модели визуализации");
    name_list.push_back("Par201; // [м], координата X \n центра эллипсоида (прямоугольника) пожара в ЗСК");
    name_list.push_back("Par202; // [м], Z");
    name_list.push_back("Par203; // [м], оси a \n (a, b) эллипсоида (прямоугольника) размера пожара");
    name_list.push_back("Par204; // [м], ост b, \n ось а - ориентация Север - Юг, ось b - Восток - Запад");
    name_list.push_back("Par205; // [л/кг], объем воды \n в ВСУ-5А (ковш)");
    name_list.push_back("Par206; // [м], глубина погружения \n ВСУ-5А (ковша) под воду - уровень воды по местной геометрической высоте");
    name_list.push_back("Par207; // [град, С], увеличение \n температуры при полете над пожаром");
    name_list.push_back("Par208; // [м/с], скорость восходящего \n потока над пожаром");
    name_list.push_back("Par209; // [ед], относительная плотность \n воздуха над пожаром");
    name_list.push_back("Par210; // [мм], амплитуда импульса \n отклонения органов управления");
    name_list.push_back("Par211; // [сек], длительность импульса");
    name_list.push_back("Par212; // [-1...1], отклонение глиссадной \n планки КПП");
    name_list.push_back("Par213; // [-1...1] - отклонение \n курсовой планки НПП");
    name_list.push_back("Par214; // [-1...1] - глиссадной");
    name_list.push_back("Par215; // [рад], (КУР) угол \n между продольной осью вертолета и направлением на радиомаяк VOR или глиссадного");
    name_list.push_back("Par216; // [м], указатель дальности \n до радиомаяка VOR в режиме НАВИГАЦИЯ или до глиссадного РМ в режиме ПОСАДКА");
    name_list.push_back("Par217; // [град] - курс \n взлета-посадки аэродрома в штурманской СК");
    name_list.push_back("Par218; // [м] - длина ВПП");
    name_list.push_back("Par219; // [м] X - \n координаты центра ВПП в ЗСК");
    name_list.push_back("Par220; // [м] Y -");
    name_list.push_back("Par221; // [м] Z -");
    name_list.push_back("Par222; // [м], удаление от \n ВПП курсового радиомаяка");
    name_list.push_back("Par223; // [град], угол полураствора \n луча курсового радиомаяка где планка реагирует");
    name_list.push_back("Par224; // [град], угол наклона \n глиссады посадки");
    name_list.push_back("Par225; // [град], угол полураствора \n луча глиссадного РМ в вертикальной плоскости, где планка отклоняется (<0.6*Uland)");
    name_list.push_back("Par226; // [км], дальность действия \n курсо-глиссадной системы (ILS)");
    name_list.push_back("Par227; // [км], дальность до \n внешнего (дальнего) маркерного радиомаяка (<0 - не установлен)");
    name_list.push_back("Par228; // [км], среднего (ближнего)");
    name_list.push_back("Par229; // [град], заданный курс \n для НПП (ГМК) (задатчик курса)");
    name_list.push_back("Par230; // [км], дальность до ближайшего");
    name_list.push_back("Par231; // [м], удаление от \n посадочного торца ВПП глиссадного РМ");
    name_list.push_back("Par232; // [град], угол полураствора \n луча курсового РМ где планка максимально отклонена");
    name_list.push_back("Par233; // [град], угол полураствора \n луча глиссадного РМ в азимутальной плоскости, где планка отклоняетя, гаснет бленкер глиссады");
    name_list.push_back("Par234; // [м], координата Х");
    name_list.push_back("Par235; // [м], Z");
    name_list.push_back("Par236; // [град], угол курсового \n луча VOR (DME) (необходимо учитывать и обратный луч +180 град.)");
    name_list.push_back("Par237; // [град], угол полураствора \n луча VOR (DME) где планка реагирует (при других углах максимально отклонена)");
    name_list.push_back("Par238; // [град], угол нечувствительности \n курсового РМ ILS или VOR (перпендикулярно лучу) в котором нет индикации To-Fr");
    name_list.push_back("Par239; // [град], угол луча \n курсового РМ в вертикальной плоскости, где гаснет бленкер курса, стрелка отклоняется");
    name_list.push_back("Par240; // [град], угол луча \n VOR (DME) в вертикальной плоскости, где гаснет бленкер курса, стрелка отклоняется");
    name_list.push_back("Par241; // [м], Y координаты \n радиомаяка дальности VOR/DME в ЗСК");
    name_list.push_back("Par242; // [км], дальность действия \n курсового РМ системы навигации (VOR/DME) (370 км - категория А - маршрут; 40 - В - аэродром)");
    name_list.push_back("Par243; // [м], длина полосы \n слива воды в проекции на пл. земли");
    name_list.push_back("Par244; // [м], ширина");
    name_list.push_back("Par245; // [град], угол курса (штурманский)");
    name_list.push_back("Par246; // [м], X - \n координата середины начала полосы слива в ЗСК");
    name_list.push_back("Par247; // [м], Z");
    name_list.push_back("Par248; //Par248");
    name_list.push_back("Par249; //Par249");
    name_list.push_back("Par250; //Par250");

    abbrevation_list.push_back("Time");
    abbrevation_list.push_back("dt");
    abbrevation_list.push_back("Hgeo");
    abbrevation_list.push_back("Hbar");
    abbrevation_list.push_back("Par005");
    abbrevation_list.push_back("Par006");
    abbrevation_list.push_back("windWx");
    abbrevation_list.push_back("windWy");
    abbrevation_list.push_back("windWYaw");
    abbrevation_list.push_back("Vx");
    abbrevation_list.push_back("Vy");
    abbrevation_list.push_back("Vz");
    abbrevation_list.push_back("Wx");
    abbrevation_list.push_back("Wy");
    abbrevation_list.push_back("Wz");
    abbrevation_list.push_back("Yaw");
    abbrevation_list.push_back("Pitch");
    abbrevation_list.push_back("Roll");
    abbrevation_list.push_back("Xg");
    abbrevation_list.push_back("Yg");
    abbrevation_list.push_back("Zg");
    abbrevation_list.push_back("G");
    abbrevation_list.push_back("dG");
    abbrevation_list.push_back("Xct");
    abbrevation_list.push_back("Yct");
    abbrevation_list.push_back("Zct");
    abbrevation_list.push_back("dXct");
    abbrevation_list.push_back("dYct");
    abbrevation_list.push_back("dZct");
    abbrevation_list.push_back("Xv");
    abbrevation_list.push_back("Xp");
    abbrevation_list.push_back("Xn");
    abbrevation_list.push_back("Xosh");
    abbrevation_list.push_back("Wnv");
    abbrevation_list.push_back("Nx");
    abbrevation_list.push_back("Ny");
    abbrevation_list.push_back("Nz");
    abbrevation_list.push_back("Vk");
    abbrevation_list.push_back("RPMnv");
    abbrevation_list.push_back("Par040");
    abbrevation_list.push_back("Par041");
    abbrevation_list.push_back("Par042");
    abbrevation_list.push_back("Par043");
    abbrevation_list.push_back("Vpr");
    abbrevation_list.push_back("Par045");
    abbrevation_list.push_back("Ax");
    abbrevation_list.push_back("Ay");
    abbrevation_list.push_back("Az");
    abbrevation_list.push_back("Par049");
    abbrevation_list.push_back("Par050");
    abbrevation_list.push_back("Alpha");
    abbrevation_list.push_back("Beta");
    abbrevation_list.push_back("AlphaNV");
    abbrevation_list.push_back("Par054");
    abbrevation_list.push_back("Par055");
    abbrevation_list.push_back("A0");
    abbrevation_list.push_back("A1");
    abbrevation_list.push_back("B1");
    abbrevation_list.push_back("Par059");
    abbrevation_list.push_back("Par060");
    abbrevation_list.push_back("Par061");
    abbrevation_list.push_back("AlphaRV");
    abbrevation_list.push_back("Par063");
    abbrevation_list.push_back("Par064");
    abbrevation_list.push_back("Par065");
    abbrevation_list.push_back("Par066");
    abbrevation_list.push_back("Par067");
    abbrevation_list.push_back("Par068");
    abbrevation_list.push_back("Par069");
    abbrevation_list.push_back("Par070");
    abbrevation_list.push_back("Par071");
    abbrevation_list.push_back("Par072");
    abbrevation_list.push_back("Par073");
    abbrevation_list.push_back("Par074");
    abbrevation_list.push_back("Par075");
    abbrevation_list.push_back("Par076");
    abbrevation_list.push_back("Par077");
    abbrevation_list.push_back("Par078");
    abbrevation_list.push_back("Par079");
    abbrevation_list.push_back("Par080");
    abbrevation_list.push_back("Par081");
    abbrevation_list.push_back("Par082");
    abbrevation_list.push_back("Par083");
    abbrevation_list.push_back("Par084");
    abbrevation_list.push_back("Par085");
    abbrevation_list.push_back("Capa");
    abbrevation_list.push_back("Zeta");
    abbrevation_list.push_back("Fosh");
    abbrevation_list.push_back("Foshrv");
    abbrevation_list.push_back("Par090");
    abbrevation_list.push_back("Roh");
    abbrevation_list.push_back("Ph");
    abbrevation_list.push_back("Th");
    abbrevation_list.push_back("Ah");
    abbrevation_list.push_back("Par095");
    abbrevation_list.push_back("Par096_Xb");
    abbrevation_list.push_back("Par097_Xk");
    abbrevation_list.push_back("Par098_Xp");
    abbrevation_list.push_back("Par099_Fosh");
    abbrevation_list.push_back("Par100_Ecor");
    abbrevation_list.push_back("Par101");
    abbrevation_list.push_back("Par102");
    abbrevation_list.push_back("Par103");
    abbrevation_list.push_back("Par104");
    abbrevation_list.push_back("Par105");
    abbrevation_list.push_back("Par106");
    abbrevation_list.push_back("Par107");
    abbrevation_list.push_back("Par108");
    abbrevation_list.push_back("Par109");
    abbrevation_list.push_back("Par110");
    abbrevation_list.push_back("Par111");
    abbrevation_list.push_back("Par112");
    abbrevation_list.push_back("Par113");
    abbrevation_list.push_back("Par114");
    abbrevation_list.push_back("Par115");
    abbrevation_list.push_back("Par116");
    abbrevation_list.push_back("Par117");
    abbrevation_list.push_back("Par118");
    abbrevation_list.push_back("Par119");
    abbrevation_list.push_back("Par120");
    abbrevation_list.push_back("Par121");
    abbrevation_list.push_back("Par122");
    abbrevation_list.push_back("Par123");
    abbrevation_list.push_back("Par124");
    abbrevation_list.push_back("Par125");
    abbrevation_list.push_back("Par126");
    abbrevation_list.push_back("Par127");
    abbrevation_list.push_back("Par128");
    abbrevation_list.push_back("Par129");
    abbrevation_list.push_back("Par130");
    abbrevation_list.push_back("Par131");
    abbrevation_list.push_back("Par132");
    abbrevation_list.push_back("Par133");
    abbrevation_list.push_back("Par134");
    abbrevation_list.push_back("Par135");
    abbrevation_list.push_back("Par136");
    abbrevation_list.push_back("Par137");
    abbrevation_list.push_back("Par138");
    abbrevation_list.push_back("Par139");
    abbrevation_list.push_back("Par140");
    abbrevation_list.push_back("Par141");
    abbrevation_list.push_back("Par142");
    abbrevation_list.push_back("Par143");
    abbrevation_list.push_back("Par144");
    abbrevation_list.push_back("Par145");
    abbrevation_list.push_back("Par146");
    abbrevation_list.push_back("Par147");
    abbrevation_list.push_back("Par148");
    abbrevation_list.push_back("Par149");
    abbrevation_list.push_back("Par150");
    abbrevation_list.push_back("Par151");
    abbrevation_list.push_back("Par152");
    abbrevation_list.push_back("Par153");
    abbrevation_list.push_back("Par154");
    abbrevation_list.push_back("Par155");
    abbrevation_list.push_back("Par156");
    abbrevation_list.push_back("Par157");
    abbrevation_list.push_back("Par158");
    abbrevation_list.push_back("Par159");
    abbrevation_list.push_back("Par160");
    abbrevation_list.push_back("Par161");
    abbrevation_list.push_back("Par162");
    abbrevation_list.push_back("Par163");
    abbrevation_list.push_back("Par164");
    abbrevation_list.push_back("Par165");
    abbrevation_list.push_back("Par166");
    abbrevation_list.push_back("Par167");
    abbrevation_list.push_back("Par168");
    abbrevation_list.push_back("Par169");
    abbrevation_list.push_back("Par170");
    abbrevation_list.push_back("Par171");
    abbrevation_list.push_back("Par172");
    abbrevation_list.push_back("Par173");
    abbrevation_list.push_back("Par174");
    abbrevation_list.push_back("Par175");
    abbrevation_list.push_back("Par176");
    abbrevation_list.push_back("Par177");
    abbrevation_list.push_back("Par178");
    abbrevation_list.push_back("Par179");
    abbrevation_list.push_back("Par180");
    abbrevation_list.push_back("Par181");
    abbrevation_list.push_back("Par182");
    abbrevation_list.push_back("Par183");
    abbrevation_list.push_back("Par184");
    abbrevation_list.push_back("Par185");
    abbrevation_list.push_back("Par186");
    abbrevation_list.push_back("Par187");
    abbrevation_list.push_back("Par188");
    abbrevation_list.push_back("Par189");
    abbrevation_list.push_back("Par190");
    abbrevation_list.push_back("Par191");
    abbrevation_list.push_back("Par192");
    abbrevation_list.push_back("Par193");
    abbrevation_list.push_back("Par194");
    abbrevation_list.push_back("Par195");
    abbrevation_list.push_back("Par196");
    abbrevation_list.push_back("Par197");
    abbrevation_list.push_back("Par198");
    abbrevation_list.push_back("Par199");
    abbrevation_list.push_back("Par200");
    abbrevation_list.push_back("Par201");
    abbrevation_list.push_back("Par202");
    abbrevation_list.push_back("Par203");
    abbrevation_list.push_back("Par204");
    abbrevation_list.push_back("Par205");
    abbrevation_list.push_back("Par206");
    abbrevation_list.push_back("Par207");
    abbrevation_list.push_back("Par208");
    abbrevation_list.push_back("Par209");
    abbrevation_list.push_back("Par210");
    abbrevation_list.push_back("Par211");
    abbrevation_list.push_back("Par212");
    abbrevation_list.push_back("Par213");
    abbrevation_list.push_back("Par214");
    abbrevation_list.push_back("Par215");
    abbrevation_list.push_back("Par216");
    abbrevation_list.push_back("Par217");
    abbrevation_list.push_back("Par218");
    abbrevation_list.push_back("Par219");
    abbrevation_list.push_back("Par220");
    abbrevation_list.push_back("Par221");
    abbrevation_list.push_back("Par222");
    abbrevation_list.push_back("Par223");
    abbrevation_list.push_back("Par224");
    abbrevation_list.push_back("Par225");
    abbrevation_list.push_back("Par226");
    abbrevation_list.push_back("Par227");
    abbrevation_list.push_back("Par228");
    abbrevation_list.push_back("Par229");
    abbrevation_list.push_back("Par230");
    abbrevation_list.push_back("Par231");
    abbrevation_list.push_back("Par232");
    abbrevation_list.push_back("Par233");
    abbrevation_list.push_back("Par234");
    abbrevation_list.push_back("Par235");
    abbrevation_list.push_back("Par236");
    abbrevation_list.push_back("Par237");
    abbrevation_list.push_back("Par238");
    abbrevation_list.push_back("Par239");
    abbrevation_list.push_back("Par240");
    abbrevation_list.push_back("Par241");
    abbrevation_list.push_back("Par242");
    abbrevation_list.push_back("Par243");
    abbrevation_list.push_back("Par244");
    abbrevation_list.push_back("Par245");
    abbrevation_list.push_back("Par246");
    abbrevation_list.push_back("Par247");
    abbrevation_list.push_back("Par248");
    abbrevation_list.push_back("Par249");
    abbrevation_list.push_back("Par250");
}

DeleteWidget::DeleteWidget(quint16 width, quint16 height)
    : ControlWidget(width, height)
{
    setWindowTitle(__FUNCTION__);

    cb->addItems(selected_list);
    connect(cb, SIGNAL(activated(int)), this, SLOT(set_index(int)));

    btn->setText("Удалить параметр");
    connect(btn, SIGNAL(clicked()), this, SLOT(delete_param()));

    layout->addWidget(cb);
    layout->addWidget(btn);
}

DeleteWidget::~DeleteWidget()
{

}

void DeleteWidget::delete_param()
{
    if (!selected_list.empty())
    {
        selected_list.removeAt(cw_index);
        cb->removeItem(cw_index);
        emit ready_delete();
    }
}

