use testdb;
drop procedure if exists create_user;
delimiter //
create procedure create_user()
begin
    declare i int default 0;
    declare username varchar(100);
    declare p_sql varchar(100);
    while i < 10000 do
        set i = i+1;
        set username = concat('testuser_', i);
        -- select username;
        set p_sql = concat('create user \'', username);
        set p_sql = concat(p_sql, '\'@\'%\' identified by \'123456\';');
        -- select p_sql;
        set @cr_sentence = p_sql;
        -- prepare ec from @cr_sentence;
        prepare ec from @cr_sentence;
        execute ec;
    end while ;
end //
delimiter ;
