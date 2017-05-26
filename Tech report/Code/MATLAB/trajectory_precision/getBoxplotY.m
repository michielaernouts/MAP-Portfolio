%put all delta_y values in one column
delta_y = [delta_test1(:,2); delta_test2(:,2);delta_test3(:,2); delta_test4(:,2);delta_test5(:,2); delta_test6(:,2);delta_test7(:,2); delta_test8(:,2);delta_test9(:,2); delta_test10(:,2);];
%group them per test
g_y = [repmat(1,length(delta_test1(:,2)),1);repmat(2,length(delta_test2(:,2)),1);repmat(3,length(delta_test3(:,2)),1);repmat(4,length(delta_test4(:,2)),1);repmat(5,length(delta_test5(:,2)),1);repmat(6,length(delta_test6(:,2)),1);repmat(7,length(delta_test7(:,2)),1);repmat(8,length(delta_test8(:,2)),1);repmat(9,length(delta_test9(:,2)),1);repmat(10,length(delta_test10(:,2)),1);];

%plot
boxplot(delta_y,g_y)
xlabel('Trajectory')
ylabel('Error [m]')
%title('RGB-D SLAM Y-Axis Precision')