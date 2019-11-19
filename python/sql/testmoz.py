#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from moz_sql_parser import parse

import json

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

# sql = "select count(1) from jobs"

print(json.dumps(parse(sql)))
