%绘制路径曲线




% 定义参数a和l
a = 0.4;
l = 0.4;

% 定义参数u的范围
u = linspace(0, pi, 1000); % 生成从0到pi的1000个点

% 根据参数方程计算x和y坐标
x = -2*a .* ((l - cos(u)) .* cos(u) +( 1 - l));
y = 2*a .* (l - cos(u)) .* sin(u);

% 绘制曲线
plot(x, y);
axis equal; % 保持x和y轴的刻度一致
grid on;    % 显示网格
title('Bridge of Death Center Line');
xlabel('x');
ylabel('y');


%% 
%动态绘图



% 定义参数a和l
a = 0.4;
l = 0.4;

% 初始化图像
figure;
hold on; % 保持当前图像，以便在上面绘制新的图形

% 用于绘制曲线的句柄
h = plot(0, 0, 'b-'); % 使用蓝色虚线，初始点设置为(0,0)，不显示

% 定义参数u的范围
u_values = linspace(0, pi, 1000); % 生成从0到pi的1000个点

% 设置坐标轴的范围，这里使用预估的范围，避免重新计算
axis([-a*3 a*3 -a*3 a*3]);
axis equal; % 保持x和y轴的刻度一致
grid on;    % 显示网格
title('Dynamic Plot of Bridge of Death Center Line'); % 添加标题
xlabel('x'); % 添加x轴标签
ylabel('y'); % 添加y轴标签

% 初始化x和y变量
x = NaN(size(u_values, 2));
y = NaN(size(u_values, 2));

% 动态绘制曲线
for i = 1:length(u_values)
    % 计算当前点的x和y坐标
    x(i) = -2*a .* ((l - cos(u_values(i))) .* cos(u_values(i)) + (1 - l));
    y(i) = 2*a .* (l - cos(u_values(i))) .* sin(u_values(i));

    % 更新曲线显示部分
    set(h, 'XData', x(1:i), 'YData', y(1:i));

    % 计算当前点的斜率 dy/du，使用中心差分法
    if i == 1
        dydu = (y(2) - y(1)) / (u_values(2) - u_values(1)); % 第一个点的斜率
    elseif i == length(u_values)
        dydu = (y(end) - y(end-1)) / (u_values(end) - u_values(end-1)); % 最后一个点的斜率
    else
        dydu = (y(i+1) - y(i-1)) / (u_values(i+1) - u_values(i-1)); % 中心差分
    end

    % 根据斜率调整绘制速度，斜率越大，延时越小
    pause_time = max(0.001, 0.001 / abs(dydu)); % 基本延时为0.01，根据斜率调整

    % 使图形更新可见
    drawnow;

    % 延时，以便观察动态效果
    pause(pause_time);
end

% 完成绘制后，释放hold on状态
hold off;

%% 

%单独绘制两个方向上的速度（导数）




% 定义参数 u 的范围
u = linspace(0, pi, 1000); % 参数 u 从 0 到 2*pi

% 计算 x'(u) 和 y'(u) 的绝对值
x_prime = sin(u) .* (0.32 - 1.6*cos(u));
y_prime = 4/25 *(2* cos(u) - 5* cos(2*u));

% 绘制 x'(u) 的图像
figure; % 创建一个新的图形窗口
plot(u, x_prime);
title('Plot of x''(u)');
xlabel('Parameter u');
ylabel('x''(u)');
grid on; % 显示网格

% 绘制 y'(u) 的图像
figure; % 创建另一个新的图形窗口
plot(u, y_prime);
title('Plot of y''(u)');
xlabel('Parameter u');
ylabel('y''(u)');
grid on; % 显示网格
%% 

%每个点的切线向量





% 给定参数
a = 0.4;
l = 0.4;

% 定义参数 u 的范围
u = linspace(0, pi, 100); % 生成从0到pi的100个点

% 根据参数方程计算x和y坐标
x = -2*a .* ((l - cos(u)) .* cos(u) + (1 - l));
y = 2*a .* (l - cos(u)) .* sin(u);

% 已知的导数表达式
x_prime = sin(u) .* (0.32 - 1.6*cos(u));
y_prime = 4/25 *(2* cos(u) - 5* cos(2*u));

% 绘制曲线 x(u) 和 y(u)
figure;
plot(x, y, 'b'); % 'b' 表示蓝色线条
axis equal; % 保持横纵坐标刻度一致
grid on;     % 显示网格
title('Curve Defined by Parametric Equation and Its Tangent Vectors');
xlabel('x');
ylabel('y');

% 在曲线上绘制切向量
quiver(x, y, x_prime, y_prime, 0, 'r');


%% 

%合速度大小和角度变化曲线




% 定义参数 u 的范围
u = linspace(0,pi, 1000); % 生成从0到2*pi的1000个点

% 给定的导数表达式
x_prime = sin(u) .* (0.32 - 1.6*cos(u));
y_prime =  4/25 *(2* cos(u) - 5* cos(2*u));

% 计算合向量的大小（长度）
magnitude = sqrt(x_prime.^2 + y_prime.^2);

% 计算合向量与x轴的角度（角速度），使用 atan2 来获得正确范围的角度值
angle = atan2(y_prime, x_prime);

% 绘制合向量大小的曲线
figure;
plot(u, magnitude);
title('Magnitude of the Composite Vector Without Absolute Value');
xlabel('Parameter u');
ylabel('Magnitude');

grid on; % 显示网格

% 绘制角度变化的曲线
figure;
plot(u, angle);
title('Angle of the Composite Vector (Angular Velocity) Without Absolute Value');
xlabel('Parameter u');
ylabel('Angle (radians)');
grid on; % 显示网格


%% 

%拟合角度变化曲线








% 定义参数 u 的范围
u = linspace(0, pi, 1000); % 生成从0到pi的1000个点

% 给定的导数表达式
x_prime = sin(u) .* (0.32 - 1.6*cos(u));
y_prime =  4/25 *(2* cos(u) - 5* cos(2*u));

% 计算合向量与x轴的角度（角速度），使用 atan2 来获得正确范围的角度值
angle = atan2(y_prime, x_prime);

% 绘制角度变化的曲线
figure;
subplot(1, 1, 1); % 使用 subplot 确保只有一个图表
plot(u, angle, 'b'); % 绘制原角度变化曲线，'b' 表示蓝色线条
title('Angle of the Composite Vector and Its Polynomial Fit');
xlabel('Parameter u');
ylabel('Angle (radians)');
grid on; % 显示网格

% 使用多项式拟合角度变化曲线
% p 是拟合多项式的阶数，可以根据需要调整
p = 11;
coefficients = polyfit(u, angle, p);
poly_angle = polyval(coefficients, u);

% 绘制拟合后的曲线
hold on; % 保持当前图形，以便在同一图形上绘制拟合曲线
plot(u, poly_angle, 'r--'); % 'r--' 表示红色虚线，表示拟合曲线
hold off; % 释放图形

% 显示拟合多项式的系数
title(['Angle of the Composite Vector (Angular Velocity) With Polynomial Fit of Degree ', num2str(p)]);




%% 
%计算曲率






% 引入MATLAB的符号计算工具箱
syms u

% 定义参数方程的一阶导数
x_prime = sin(u) * (0.32 - 1.6 * cos(u));
y_prime =  4/25 *(2* cos(u) - 5* cos(2*u));

% 定义参数方程的二阶导数
x_double_prime = 0.32 * cos(u) - 1.6 * cos(2 * u);
y_double_prime = -8/25 *(sin(u) - 5 *sin(2* u));

% 使用曲率公式计算k
k_expression = abs(x_prime * y_double_prime - y_prime * x_double_prime) / ((x_prime^2 + y_prime^2)^(3/2));

% 将符号表达式转换为MATLAB的函数句柄
k_func = matlabFunction(k_expression);

% 选择u的一个合适的范围进行数值计算，这里我们选择从0到pi
u_values = linspace(0, pi, 1000); % 生成1000个点位于[0, pi]区间内

% 计算k的数值
k_values = k_func(u_values);

% 计算曲率半径R的数值，R = 1/|k|
R_values = 1./abs(k_values);

% 绘制曲率k关于u的图像
figure; % 创建一个新的图形窗口
subplot(2, 1, 1); % 创建一个2x1的子图网格，并定位到第一个子图
plot(u_values, k_values, 'LineWidth', 2); % 绘制曲线
title('曲率 k 关于参数 u 的图像'); % 添加标题
xlabel('参数 u'); % 添加x轴标签
ylabel('曲率 k'); % 添加y轴标签
grid on; % 显示网格

% 绘制曲率半径R关于u的图像
subplot(2, 1, 2); % 创建一个2x1的子图网格，并定位到第二个子图
plot(u_values, R_values, 'LineWidth', 2); % 绘制曲线
title('曲率半径 R 关于参数 u 的图像'); % 添加标题
xlabel('参数 u'); % 添加x轴标签
ylabel('曲率半径 R'); % 添加y轴标签
grid on; % 显示网格


%% 
%曲率半径拟合




% 定义参数u
syms u

% 根据您提供的导数表达式
x_prime = sin(u) * (0.32 - 1.6 * cos(u));
y_prime =  4/25 *(2* cos(u) - 5* cos(2*u));
x_double_prime = 0.32 * cos(u) - 1.6 * cos(2 * u);
y_double_prime = -8/25 *(sin(u) - 5 *sin(2* u));

% 使用曲率公式计算k
k_expression = abs(x_prime * y_double_prime - y_prime * x_double_prime) / ((x_prime^2 + y_prime^2)^(3/2));

% 定义曲率半径R的符号表达式
R_expression = 1 / abs(k_expression);

% 将R的符号表达式转换为MATLAB的函数句柄
R_func = matlabFunction(R_expression);

% 选择u的一个合适的范围进行数值计算，这里我们选择从0到2*pi
u_values = linspace(0, pi,100 ); % 生成1000个点位于[0, 2*pi]区间内

% 计算R的数值
R_values = arrayfun(R_func, u_values); % 使用arrayfun来应用函数句柄

% 使用多项式拟合R的数值数据，这里我们使用5阶多项式进行拟合
p = polyfit(u_values, R_values, 5);

% 利用多项式系数生成多项式函数句柄
p_func = @(u) polyval(p, u);

% 绘制原始曲率半径R关于u的图像
figure; % 创建一个新的图形窗口
subplot(2, 1, 1); % 创建一个2x1的子图网格，并定位到第一个子图
plot(u_values, R_values, 'b', 'LineWidth', 2); % 绘制原始曲率半径R的曲线
hold on; % 保持当前图像，以便在同一图像上绘制多项式拟合曲线

% 绘制多项式拟合后的曲率半径关于u的图像
plot(u_values, p_func(u_values), 'r--', 'LineWidth', 2); % 绘制多项式拟合曲线
title('曲率半径 R 原函数与多项式拟合结果'); % 添加标题
xlabel('参数 u'); % 添加x轴标签
ylabel('曲率半径 R'); % 添加y轴标签
legend('原函数', '多项式拟合'); % 添加图例
grid on; % 显示网格

% 显示多项式拟合的阶数和系数
disp('多项式拟合的阶数和系数：');
disp(['阶数: ', num2str(length(p))]);
disp('系数：');
disp(p);



%% 


%u与曲线半径的变化函数








% 定义参数u
syms u

% 定义导数表达式
x_prime = sin(u) * (0.32 - 1.6 * cos(u));
y_prime = 4/25 *(2* cos(u) - 5* cos(2*u));

% 定义弧长积分表达式
arc_length_integrand = sqrt(x_prime^2 + y_prime^2);

% 将弧长积分表达式转换为 MATLAB 函数句柄
arc_length_func = matlabFunction(arc_length_integrand);

% 定义u的范围
u_values = linspace(0, pi, 10000); % 在[0, pi]区间内生成100个点

% 数值积分计算弧长
arc_length_values = cumtrapz(u_values, arrayfun(arc_length_func, u_values));

% 绘制弧长变化图像
figure; % 创建一个新的图形窗口
plot(u_values, arc_length_values, 'b', 'LineWidth', 2); % 绘制弧长变化曲线
title('随着u的变化曲线长度的变化'); % 添加标题
xlabel('参数 u'); % 添加x轴标签
ylabel('曲线长度 L'); % 添加y轴标签
grid on; % 显示网格

% 显示弧长结果
disp('随着u的变化曲线长度的变化：');
disp(arc_length_values);


%% 


% 长度与曲率半径之间的函数
% 曲率半径拟合
   
% 定义参数u
syms u

% 根据您提供的导数表达式
x_prime = sin(u) * (0.32 - 1.6 * cos(u));
y_prime = 4/25 * (2 * cos(u) - 5 * cos(2 * u));
x_double_prime = 0.32 * cos(u) - 1.6 * cos(2 * u);
y_double_prime = -8/25 * (sin(u) - 5 * sin(2 * u));

% 使用曲率公式计算k
k_expression = abs(x_prime * y_double_prime - y_prime * x_double_prime) / ((x_prime^2 + y_prime^2)^(3/2));

% 定义曲率半径R的符号表达式
R_expression = 1 / abs(k_expression);

% 将R的符号表达式转换为MATLAB的函数句柄
R_func = matlabFunction(R_expression);

% 选择u的一个合适的范围进行数值计算，这里我们选择从0到pi
u_values = linspace(0, pi, 10000); % 生成100个点位于[0, pi]区间内

% 计算R的数值
R_values = arrayfun(R_func, u_values); % 使用arrayfun来应用函数句柄

% 计算弧长

% 定义导数表达式
arc_length_integrand = sqrt(x_prime^2 + y_prime^2);

% 将弧长积分表达式转换为 MATLAB 函数句柄
arc_length_func = matlabFunction(arc_length_integrand);

% 使用与R_values相同的u_values范围
u_values = linspace(0, pi, 10000); % 在[0, pi]区间内生成100个点

% 数值积分计算弧长
arc_length_values = cumtrapz(u_values, arrayfun(arc_length_func, u_values));

% 确保arc_length_values和R_values长度相同
if length(arc_length_values) > length(R_values)
    arc_length_values = arc_length_values(1:length(R_values));
elseif length(R_values) > length(arc_length_values)
    R_values = R_values(1:length(arc_length_values));
end

% 绘制曲率半径与弧长之间的关系图像
figure; % 创建一个新的图形窗口
plot(arc_length_values, R_values, 'b', 'LineWidth', 2); % 绘制曲率半径与弧长的关系图
hold on; % 保持当前图像，以便在同一图像上绘制多项式拟合曲线

% 使用多项式拟合R与L的关系，这里我们使用5阶多项式进行拟合
p_R_L = polyfit(arc_length_values, R_values, 5);

% 利用多项式系数生成多项式函数句柄
p_R_L_func = @(L) polyval(p_R_L, L);

% 绘制多项式拟合后的R与L的关系图像
plot(arc_length_values, p_R_L_func(arc_length_values), 'r--', 'LineWidth', 2); % 绘制多项式拟合曲线
title('曲率半径 R 与曲线长度 L 之间的关系及其多项式拟合'); % 添加标题
xlabel('曲线长度 L'); % 添加x轴标签
ylabel('曲率半径 R'); % 添加y轴标签
legend('原函数', '多项式拟合'); % 添加图例
grid on; % 显示网格

% 显示多项式拟合的阶数和系数
disp('曲率半径 R 与曲线长度 L 之间关系的多项式拟合的阶数和系数：');
disp(['阶数: ', num2str(length(p_R_L))]);
disp('系数：');
disp(p_R_L);
