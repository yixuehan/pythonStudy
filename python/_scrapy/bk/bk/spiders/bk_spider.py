#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import scrapy
import json


class BooksSpider(scrapy.Spider):
    name = "bk"
    start_urls = ['http://books.toscrape.com/']
    custom_settings = {
            "LOG_LEVEL": "ERROR",
            }

    def __init__(self):
        self.__results = []

    def parse(self, response):
        print(response.css('article.product_pod'))
        for book in response.css('article.product_pod'):
            name = book.xpath('./h3/a/@title').extract_first()

            price = book.css('p.price_color::text').extract_first()

            self.__results.append({
                'name': name,
                'price': price,
            })

        next_url = response.css('ul.paper li.next a::attr(href)').extract_first()
        if next_url:
            next_url = response.urljoin(next_url)
            yield scrapy.Request(next_url, calback=self.parse)
        else:
            with open("books.json", "w") as f:
                f.write(json.dumps(self.__results))

    def parse_book(self, response):
        for book in response.css('article.product_pod'):
            name = book.xpath('./h3/a/@title').extract_first()

            price = book.css('p.price_color::text').extract_first()

            self.__results.append({
                'name': name,
                'price': price,
            })

        next_url = response.css('ul.paper li.next a::attr(href)').extract_first()
        if next_url:
            next_url = response.urljoin(next_url)
            yield scrapy.Request(next_url, calback=self.parse_book)
        else:
            with open("parse_book.json", "w") as f:
                f.write(json.dumps(self.__results))

    def start_requests(self):
        # import pdb;
        # pdb.set_trace()
        start_urls = ['http://books.toscrape.com/']
        for url in start_urls:
            yield scrapy.Request(url=url,
                                 callback=self.parse,
                                 headers={'User-Agent': 'Mozilla/5.0'},
                                 dont_filter=True,
                                 )
