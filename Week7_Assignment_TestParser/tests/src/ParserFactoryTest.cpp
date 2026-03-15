#include <gtest/gtest.h>
#include "ParserFactory.h"
#include "CsvParser.h"
#include "JsonParser.h"
#include "XmlParser.h"

TEST(ParserFactoryTest, GivenJsonFilePath_WhenCreate_ThenReturnsNonNullPtr)
{
    IParser* parser = ParserFactory::create("tests/docs/sample.json");
    ASSERT_NE(parser, nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenJsonFilePath_WhenCreate_ThenReturnsJsonParserInstance)
{
    IParser* parser = ParserFactory::create("tests/docs/sample.json");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<JsonParser*>(parser), nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenCsvFilePath_WhenCreate_ThenReturnsNonNullPtr)
{
    IParser* parser = ParserFactory::create("tests/docs/sample.csv");
    ASSERT_NE(parser, nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenCsvFilePath_WhenCreate_ThenReturnsCsvParserInstance)
{
    IParser* parser = ParserFactory::create("tests/docs/sample.csv");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<CsvParser*>(parser), nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenXmlFilePath_WhenCreate_ThenReturnsNonNullPtr)
{
    IParser* parser = ParserFactory::create("tests/docs/sample.xml");
    ASSERT_NE(parser, nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenXmlFilePath_WhenCreate_ThenReturnsXmlParserInstance)
{
    IParser* parser = ParserFactory::create("tests/docs/sample.xml");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<XmlParser*>(parser), nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenUnsupportedExtension_WhenCreate_ThenReturnsNullptr)
{
    IParser* parser = ParserFactory::create("tests/docs/sample.txt");
    EXPECT_EQ(parser, nullptr);
}

TEST(ParserFactoryTest, GivenNoDotInPath_WhenCreate_ThenReturnsNullptr)
{
    IParser* parser = ParserFactory::create("tests/docs/noextension");
    EXPECT_EQ(parser, nullptr);
}

TEST(ParserFactoryTest, GivenEmptyString_WhenCreate_ThenReturnsNullptr)
{
    IParser* parser = ParserFactory::create("");
    EXPECT_EQ(parser, nullptr);
}

TEST(ParserFactoryTest, GivenUpperCaseJsonExtension_WhenCreate_ThenReturnsJsonParser)
{
    IParser* parser = ParserFactory::create("tests/docs/sample.JSON");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<JsonParser*>(parser), nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenUpperCaseCsvExtension_WhenCreate_ThenReturnsCsvParser)
{
    IParser* parser = ParserFactory::create("tests/docs/sample.CSV");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<CsvParser*>(parser), nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenUpperCaseXmlExtension_WhenCreate_ThenReturnsXmlParser)
{
    IParser* parser = ParserFactory::create("tests/docs/sample.XML");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<XmlParser*>(parser), nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenPdfExtension_WhenCreate_ThenReturnsNullptr)
{
    IParser* parser = ParserFactory::create("tests/docs/sample.pdf");
    EXPECT_EQ(parser, nullptr);
}

TEST(ParserFactoryTest, GivenMixedCaseExtension_WhenCreate_ThenReturnsCorrectParser)
{
    IParser* parser = ParserFactory::create("tests/docs/sample.Json");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<JsonParser*>(parser), nullptr);
    delete parser;
}
