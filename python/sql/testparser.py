#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sqlparse
from util.python.database import mysql


def sql_format(sql):
    stmts = sqlparse.split(sql)
    # print(stmts)
    rets = []
    for stmt in stmts:
        rets.append(sqlparse.format(stmt, reindent=True, keyword_case="upper"))
    print("format sql:", rets)
    return rets


def sql_parse(sql):
    # sqls = sql_format(sql)
    sqls = [sql]
    for sql in sqls:
        parse = sqlparse.parse(sql)
        assert len(parse) == 1
        ast = parse[0]
        ast_parse(ast)


def parse_table_fields(value_text):
    value_text = value_text.strip(' ()')
    fields = value_text.split(',')
    # print(fields)
    rets = []
    for field in fields:
        if mysql.contain_keyword(field):
            continue
        field = field.split()[0]
        field = field.strip(' ``')
        rets.append(field)
    print(rets)


def ast_parse(ast):
    for token in ast.tokens:
        print("[%s][%s][%s][%s]" % (type(token), token.ttype, token.value, type(token.value)))
        if isinstance(token, sqlparse.sql.Where):
            print("find where:", type(token), token.ttype, token.value, type(token.value))
        if isinstance(token, sqlparse.sql.IdentifierList):
            for identifier in token.get_identifiers():
                print("[%s][%s][%s][%s]" % (type(identifier), identifier.ttype, identifier.value, identifier.get_name()))
        if isinstance(token, sqlparse.sql.Parenthesis):
            parse_table_fields(token.value)
            # for identifier in token._groupable_tokens:
            #     print("create table field[%s][%s][%s]" % (type(identifier), identifier.ttype, identifier.value))


if __name__ == '__main__':
    sql = '''
        SELECT a.x, b.y
        FROM t_project_job a inner join t_project_project b
        on a.project_id = b.project_id
        '''
    sql_format(sql)
    sql = '''
        SELECT * FROM wangkai_dev.t_online_service_apply where service_id = srv5klnzc38ngr04'
    '''
    sql_format(sql)
    sql = '''
        select online.*, ifnull(apply.apply_id, '') as apply_id, ifnull(apply.audit_status, 'Unaudited') as audit_status,
               apply.update_time as audit_time, task.model_code_text as code_text, task.model_name, task.task_id, task.status as task_status
         from (t_online_service as online left join t_online_service_apply as apply on online.service_id = apply.service_id)
              inner join t_task as task on task.task_id = online.task_id
         where online.user_id = 'uid'
          and ('pid' = '' or online.project_id = 'pid')
          and ('sid' = '' or 'sid' = online.service_id)
          and task.task_type = 'debug'
          and online.online_service_status != 'enable'
         order by apply.update_time desc
         limit 1
    '''
    sql_format(sql)
    # sql = '''
    #     select * from a where id = 200; select * from b where id = 100
    # '''
    sql = '''
    CREATE TABLE `t_task` (
      `task_id` varchar(64) NOT NULL DEFAULT '',
      `model_id` varchar(64) NOT NULL,
      `model_file` varchar(256) NOT NULL,
      `model_ori_filename` varchar(256) NOT NULL DEFAULT '',
      `create_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
      `update_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
      `fail_reason` varchar(1024) NOT NULL DEFAULT '',
      `status` varchar(64) NOT NULL,
      `result_url` varchar(1024) NOT NULL,
      `exec_duration` int(11) NOT NULL DEFAULT '0',
      `model_name` varchar(256) NOT NULL DEFAULT '',
      `model_code_form` varchar(64) NOT NULL,
      `model_code_type` varchar(64) NOT NULL,
      `model_code_text` text NOT NULL,
      `docker_addr` varchar(1024) NOT NULL DEFAULT '',
      `running_token` varchar(1024) NOT NULL DEFAULT '',
      `result_id` varchar(256) NOT NULL DEFAULT '',
      `enable` varchar(64) NOT NULL DEFAULT '' COMMENT '是否删除   valid--未删除   delete--删除',
      `result_filename` varchar(128) NOT NULL DEFAULT '',
      `model_type` varchar(64) NOT NULL COMMENT '在线模型还是离线模型',
      `docker_port` int(11) NOT NULL DEFAULT '0' COMMENT '在线服务需要使用',
      `user_id` varchar(64) NOT NULL,
      `task_type` varchar(64) NOT NULL,
      `service_id` varchar(64) NOT NULL,
      `log` text NOT NULL,
      `project_id` varchar(64) NOT NULL,
      `sandbox_id` varchar(64) NOT NULL,
      UNIQUE KEY `task_id_UNIQUE` (`task_id`)
    ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
    '''
    for item in sqlparse.split(sql):
        print(item, '@@@@@@@@@@@@')
    # sql = '''
    # update t_task set status = ? where task_id = ?
    # '''
    # sql = '''
    # insert into t_task(task_id, status, model_id, model_name, model_file, model_code_text, model_code_form, model_code_type, model_type, model_ori_filename, user_id, fail_reason, r  esult_url,enable, docker_port, docker_addr, task_type, service_id, log, project_id, sandbox_id, running_token)
    #   values(:task_id, :status, :model_id, :model_name, :model_file, :model_code_text, :model_code_form, :model_code_type, :model_type, :model_ori_filename, :user_id, :fail_reason, :result_url,:enable, :docker_port, :docker_addr, :task_type, :service_id, :log, :project_id, :sandbox_id, :running_token)
    # '''
    sql_parse(sql)
