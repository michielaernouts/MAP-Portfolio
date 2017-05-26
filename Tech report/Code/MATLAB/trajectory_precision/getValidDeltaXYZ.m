function [ delta_xyz ] = getValidDeltaXYZ(referencevector, testvector )
%GETVALIDDELTAXYZ Get difference between test matrix and reference
%   Get difference between test matrix and reference, but delete the row if
%   the testvector timestamp does not match the reference timestamp (with
%   a threshold of 1 second)

    %init delta matrix
    delta_xyz = zeros(length(testvector),7);

    %get differences between test matrix and reference matrix
    for k=1:length(testvector)
            delta_xyz(k,1)=referencevector(k,2) - testvector(k,2);
            delta_xyz(k,2)=referencevector(k,3) - testvector(k,3);
            delta_xyz(k,3)=referencevector(k,4) - testvector(k,4);
            delta_xyz(k,4)=referencevector(k,5) - testvector(k,5);
            delta_xyz(k,5)=referencevector(k,6) - testvector(k,6);
            delta_xyz(k,6)=referencevector(k,7) - testvector(k,7);
            delta_xyz(k,7)=referencevector(k,8) - testvector(k,8);
    end

    %remove row if timestamp > reference timestamp +1 or timestamp < reference
    %timestamp -1
    for k=length(delta_xyz):-1:1
        if testvector(k,1) > referencevector(k,1)+1  || testvector(k,1) < referencevector(k,1)-1
            delta_xyz(k,:) = [];
        end
        
    end
end

