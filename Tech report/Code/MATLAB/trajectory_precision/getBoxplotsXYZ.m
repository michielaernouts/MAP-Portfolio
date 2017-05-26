%% X-axis
%put all delta_x values in one column
delta_x = [delta_test1(:,1); delta_test2(:,1);delta_test3(:,1); delta_test4(:,1);delta_test5(:,1); delta_test6(:,1);delta_test7(:,1); delta_test8(:,1);delta_test9(:,1); delta_test10(:,1);];
%group them per test
g_x = [repmat(1,length(delta_test1(:,1)),1);repmat(2,length(delta_test2(:,1)),1);repmat(3,length(delta_test3(:,1)),1);repmat(4,length(delta_test4(:,1)),1);repmat(5,length(delta_test5(:,1)),1);repmat(6,length(delta_test6(:,1)),1);repmat(7,length(delta_test7(:,1)),1);repmat(8,length(delta_test8(:,1)),1);repmat(9,length(delta_test9(:,1)),1);repmat(10,length(delta_test10(:,1)),1);];

%plot
subplot(3,1,1)
boxplot(delta_x,g_x)
xlabel('Trajectory')
ylabel('Error [m]')
title('RGB-D SLAM X-Axis Precision')

%% Y-axis
%put all delta_y values in one column
delta_y = [delta_test1(:,2); delta_test2(:,2);delta_test3(:,2); delta_test4(:,2);delta_test5(:,2); delta_test6(:,2);delta_test7(:,2); delta_test8(:,2);delta_test9(:,2); delta_test10(:,2);];
%group them per test
g_y = [repmat(1,length(delta_test1(:,2)),1);repmat(2,length(delta_test2(:,2)),1);repmat(3,length(delta_test3(:,2)),1);repmat(4,length(delta_test4(:,2)),1);repmat(5,length(delta_test5(:,2)),1);repmat(6,length(delta_test6(:,2)),1);repmat(7,length(delta_test7(:,2)),1);repmat(8,length(delta_test8(:,2)),1);repmat(9,length(delta_test9(:,2)),1);repmat(10,length(delta_test10(:,2)),1);];

%plot
subplot(3,1,2)
boxplot(delta_y,g_y)
xlabel('Trajectory')
ylabel('Error [m]')
title('RGB-D SLAM Y-Axis Precision')

%% Z-axis
%put all delta_z values in one column
delta_z = [delta_test1(:,3); delta_test2(:,3);delta_test3(:,3); delta_test4(:,3);delta_test5(:,3); delta_test6(:,3);delta_test7(:,3); delta_test8(:,3);delta_test9(:,3); delta_test10(:,3);];
%group them per test
g_z = [repmat(1,length(delta_test1(:,3)),1);repmat(2,length(delta_test2(:,3)),1);repmat(3,length(delta_test3(:,3)),1);repmat(4,length(delta_test4(:,3)),1);repmat(5,length(delta_test5(:,3)),1);repmat(6,length(delta_test6(:,3)),1);repmat(7,length(delta_test7(:,3)),1);repmat(8,length(delta_test8(:,3)),1);repmat(9,length(delta_test9(:,3)),1);repmat(10,length(delta_test10(:,3)),1);];

%plot
subplot(3,1,3)
boxplot(delta_z,g_z)
xlabel('Trajectory')
ylabel('Error [m]')
title('RGB-D SLAM Z-Axis Precision')