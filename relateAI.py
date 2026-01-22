from Tishi import system_template_text, user_template_text
from langchain.prompts import  ChatPromptTemplate
from langchain_openai import  ChatOpenAI
from langchain.output_parsers import PydanticOutputParser
from xiaohongshumoshi import Xiaohongshu

def generate_xiaohongshu(theme, openai_api_key):
    prompt = ChatPromptTemplate.from_messages([
        ("system", system_template_text),
        ("user", user_template_text)
    ])

    model = ChatOpenAI(api_key = openai_api_key,
                       base_url="https://api.deepseek.com",
                       model_name = "deepseek-chat"
                       )
    output_parser = PydanticOutputParser(pydantic_object=Xiaohongshu)
    chain = prompt | model | output_parser
    result = chain.invoke({
        "parser_instructions": output_parser.get_format_instructions(),
        "theme": theme
    })

    return result

# print(generate_xiaohongshu("大模型", "sk-acfa58b99a5849aeb5516cb76a9d16a6"))



