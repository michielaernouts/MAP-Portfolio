%put all delta_x values in one column
delta_x = [delta_test1(:,1); delta_test2(:,1);delta_test3(:,1); delta_test4(:,1);delta_test5(:,1); delta_test6(:,1);delta_test7(:,1); delta_test8(:,1);delta_test9(:,1); delta_test10(:,1);];
%group them per test
g_x = [repmat(1,length(delta_test1(:,1)),1);repmat(2,length(delta_test2(:,1)),1);repmat(3,length(delta_test3(:,1)),1);repmat(4,length(delta_test4(:,1)),1);repmat(5,length(delta_test5(:,1)),1);repmat(6,length(delta_test6(:,1)),1);repmat(7,length(delta_test7(:,1)),1);repmat(8,length(delta_test8(:,1)),1);repmat(9,length(delta_test9(:,1)),1);repmat(10,length(delta_test10(:,1)),1);];

%plot
boxplot(delta_x,g_x)
xlabel('Trajectory')
ylabel('Error [m]')
%title('RGB-D SLAM X-Axis Precision')