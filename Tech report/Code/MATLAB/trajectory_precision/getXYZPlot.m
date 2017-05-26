%% X-plot
%subplot(1,3,1)
plot(referenceestimate(:,1),referenceestimate(:,2),test1estimate(:,1),test1estimate(:,2),test2estimate(:,1),test2estimate(:,2),test3estimate(:,1),test3estimate(:,2),test4estimate(:,1),test4estimate(:,2),test5estimate(:,1),test5estimate(:,2),test6estimate(:,1),test6estimate(:,2),test7estimate(:,1),test7estimate(:,2),test8estimate(:,1),test8estimate(:,2),test9estimate(:,1),test9estimate(:,2),test10estimate(:,1),test10estimate(:,2))
xlabel('Time [epoch]')
ylabel('X-axis')
%title('RGB-D SLAM X-Axis Trajectory')

%% Y-plot
%subplot(1,3,2)
plot(referenceestimate(:,1),referenceestimate(:,3),test1estimate(:,1),test1estimate(:,3),test2estimate(:,1),test2estimate(:,3),test3estimate(:,1),test3estimate(:,3),test4estimate(:,1),test4estimate(:,3),test5estimate(:,1),test5estimate(:,3),test6estimate(:,1),test6estimate(:,3),test7estimate(:,1),test7estimate(:,3),test8estimate(:,1),test8estimate(:,3),test9estimate(:,1),test9estimate(:,3),test10estimate(:,1),test10estimate(:,3))
xlabel('Time [epoch]')
ylabel('Y-axis')
%title('RGB-D SLAM Y-Axis Trajectory')

%% Z-plot
%subplot(1,3,3)
plot(referenceestimate(:,1),referenceestimate(:,4),test1estimate(:,1),test1estimate(:,4),test2estimate(:,1),test2estimate(:,4),test3estimate(:,1),test3estimate(:,4),test4estimate(:,1),test4estimate(:,4),test5estimate(:,1),test5estimate(:,4),test6estimate(:,1),test6estimate(:,4),test7estimate(:,1),test7estimate(:,4),test8estimate(:,1),test8estimate(:,4),test9estimate(:,1),test9estimate(:,4),test10estimate(:,1),test10estimate(:,4))
xlabel('Time [epoch]')
ylabel('Z-axis')
%title('RGB-D SLAM Z-Axis Trajectory')