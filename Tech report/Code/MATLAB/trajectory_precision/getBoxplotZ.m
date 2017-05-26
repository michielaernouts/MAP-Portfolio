%put all delta_z values in one column
delta_z = [delta_test1(:,3); delta_test2(:,3);delta_test3(:,3); delta_test4(:,3);delta_test5(:,3); delta_test6(:,3);delta_test7(:,3); delta_test8(:,3);delta_test9(:,3); delta_test10(:,3);];
%group them per test
g_z = [repmat(1,length(delta_test1(:,3)),1);repmat(2,length(delta_test2(:,3)),1);repmat(3,length(delta_test3(:,3)),1);repmat(4,length(delta_test4(:,3)),1);repmat(5,length(delta_test5(:,3)),1);repmat(6,length(delta_test6(:,3)),1);repmat(7,length(delta_test7(:,3)),1);repmat(8,length(delta_test8(:,3)),1);repmat(9,length(delta_test9(:,3)),1);repmat(10,length(delta_test10(:,3)),1);];

%plot
boxplot(delta_z,g_z)
xlabel('Trajectory')
ylabel('Error [m]')
%title('RGB-D SLAM Z-Axis Precision')