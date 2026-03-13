#include <gtest/gtest.h>
#include "ParserFactory.h"
#include "CsvParser.h"
#include "JsonParser.h"
#include "XmlParser.h"

TEST(ParserFactoryTest, GivenJsonFilePath_Create_ReturnsNonNullPtr)
{
    IParser* parser = ParserFactory::create("/some/path/data.json");
    ASSERT_NE(parser, nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenJsonFilePath_Create_ReturnsJsonParserInstance)
{
    IParser* parser = ParserFactory::create("/some/path/data.json");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<JsonParser*>(parser), nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenCsvFilePath_Create_ReturnsNonNullPtr)
{
    IParser* parser = ParserFactory::create("/some/path/data.csv");
    ASSERT_NE(parser, nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenCsvFilePath_Create_ReturnsCsvParserInstance)
{
    IParser* parser = ParserFactory::create("/some/path/data.csv");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<CsvParser*>(parser), nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenXmlFilePath_Create_ReturnsNonNullPtr)
{
    IParser* parser = ParserFactory::create("/some/path/data.xml");
    ASSERT_NE(parser, nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenXmlFilePath_Create_ReturnsXmlParserInstance)
{
    IParser* parser = ParserFactory::create("/some/path/data.xml");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<XmlParser*>(parser), nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenUnsupportedExtension_Create_ReturnsNullptr)
{
    IParser* parser = ParserFactory::create("/some/path/data.txt");
    EXPECT_EQ(parser, nullptr);
}

TEST(ParserFactoryTest, GivenNoDotInPath_Create_ReturnsNullptr)
{
    IParser* parser = ParserFactory::create("/some/path/noextension");
    EXPECT_EQ(parser, nullptr);
}

TEST(ParserFactoryTest, GivenEmptyString_Create_ReturnsNullptr)
{
    IParser* parser = ParserFactory::create("");
    EXPECT_EQ(parser, nullptr);
}

TEST(ParserFactoryTest, GivenUpperCaseJsonExtension_Create_ReturnsJsonParser)
{
    IParser* parser = ParserFactory::create("/some/path/DATA.JSON");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<JsonParser*>(parser), nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenUpperCaseCsvExtension_Create_ReturnsCsvParser)
{
    IParser* parser = ParserFactory::create("/some/path/DATA.CSV");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<CsvParser*>(parser), nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenUpperCaseXmlExtension_Create_ReturnsXmlParser)
{
    IParser* parser = ParserFactory::create("/some/path/DATA.XML");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<XmlParser*>(parser), nullptr);
    delete parser;
}

TEST(ParserFactoryTest, GivenPdfExtension_Create_ReturnsNullptr)
{
    IParser* parser = ParserFactory::create("/some/path/data.pdf");
    EXPECT_EQ(parser, nullptr);
}

TEST(ParserFactoryTest, GivenMixedCaseExtension_Create_ReturnsCorrectParser)
{
    IParser* parser = ParserFactory::create("/some/path/data.Json");
    ASSERT_NE(parser, nullptr);
    EXPECT_NE(dynamic_cast<JsonParser*>(parser), nullptr);
    delete parser;
}
