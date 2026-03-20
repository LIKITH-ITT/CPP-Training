#include <gtest/gtest.h>
#include "ParserFactory.h"
#include "CsvParser.h"
#include "JsonParser.h"
#include "XmlParser.h"

const std::string JSON_PATH = "tests/docs/sample.json";
const std::string CSV_PATH = "tests/docs/sample.csv";
const std::string XML_PATH = "tests/docs/sample.xml";
const std::string JSON_UPPER_PATH = "tests/docs/json4.JSON";
const std::string JSON_MIXED_PATH = "tests/docs/sample.Json";
const std::string TXT_PATH = "tests/docs/sample.txt";
const std::string PDF_PATH = "tests/docs/sample.pdf";
const std::string NO_EXTENSION_PATH = "tests/docs/noextension";
const std::string EMPTY_PATH = "";

TEST(GivenParserFactoryTest, WhenJsonFilePath_ThenReturnsNonNullPtr)
{
    IParser* parser = ParserFactory::create(JSON_PATH);
    ASSERT_NE(parser, nullptr);
    delete parser;
}

TEST(GivenParserFactoryTest, WhenJsonFilePath_ThenReturnsJsonParserInstance)
{
    IParser* parser = ParserFactory::create(JSON_PATH);
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<JsonParser*>(parser), nullptr);
    delete parser;
}

TEST(GivenParserFactoryTest, WhenCsvFilePath_ThenReturnsNonNullPtr)
{
    IParser* parser = ParserFactory::create(CSV_PATH);
    ASSERT_NE(parser, nullptr);
    delete parser;
}

TEST(GivenParserFactoryTest, WhenCsvFilePath_ThenReturnsCsvParserInstance)
{
    IParser* parser = ParserFactory::create(CSV_PATH);
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<CsvParser*>(parser), nullptr);
    delete parser;
}

TEST(GivenParserFactoryTest, WhenXmlFilePath_ThenReturnsNonNullPtr)
{
    IParser* parser = ParserFactory::create(XML_PATH);
    ASSERT_NE(parser, nullptr);
    delete parser;
}

TEST(GivenParserFactoryTest, WhenXmlFilePath_ThenReturnsXmlParserInstance)
{
    IParser* parser = ParserFactory::create(XML_PATH);
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<XmlParser*>(parser), nullptr);
    delete parser;
}

TEST(GivenParserFactoryTest, WhenUnsupportedExtension_ThenReturnsNullptr)
{
    IParser* parser = ParserFactory::create(TXT_PATH);
    EXPECT_EQ(parser, nullptr);
}

TEST(GivenParserFactoryTest, WhenNoDotInPath_ThenReturnsNullptr)
{
    IParser* parser = ParserFactory::create(NO_EXTENSION_PATH);
    EXPECT_EQ(parser, nullptr);
}

TEST(GivenParserFactoryTest, WhenEmptyString_ThenReturnsNullptr)
{
    IParser* parser = ParserFactory::create(EMPTY_PATH);
    EXPECT_EQ(parser, nullptr);
}

TEST(GivenParserFactoryTest, WhenUpperCaseExtension_ThenReturnsCorrectParser)
{
    IParser* parser = ParserFactory::create(JSON_UPPER_PATH);
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<JsonParser*>(parser), nullptr);
    delete parser;
}

TEST(GivenParserFactoryTest, WhenPdfExtension_ThenReturnsNullptr)
{
    IParser* parser = ParserFactory::create(PDF_PATH);
    EXPECT_EQ(parser, nullptr);
}

TEST(GivenParserFactoryTest, WhenMixedCaseExtension_ThenReturnsCorrectParser)
{
    IParser* parser = ParserFactory::create(JSON_MIXED_PATH);
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<JsonParser*>(parser), nullptr);
    delete parser;
}