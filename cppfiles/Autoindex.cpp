#include "../headers/Autoindex.hpp"

Autoindex::Autoindex(const std::string &path,std::string &o_path) : path_d(""),
												index(""),
												path("")
{

	this->path_d += path;
	this->path += o_path;
	generateIndexPage();
}

Autoindex::~Autoindex() {}

std::string Autoindex::create_header()
{
	std::string header;

	header = "<!DOCTYPE html>\n\
    <html>\n\
        <head>\n\
            <title>Autoindex</title>\n\
			<meta charset=\"UTF-8\">\n\
        </head>\n\
		<style>\n\
			h1 {font-family: \"Times New Roman\";}\n\
			table {font-family: \"Courier New\";}\n\
			.border {text-align: start; border-bottom-style: solid; border-width: 1px;}\n\
		</style>\n\
        <body>\n\
        	<h1>Index of " +
			 path + "</h1>\n\
            <table style=\"width:100%\">\n\
				<colgroup span=\"20\"></colgroup>\n\
				<tr>\n\
					<th class=\"border\">Link</th>\n";
	return (header);
}

std::string Autoindex::footer()
{
	std::string footer;

	footer = "\t\t\t</table>\n\
		</body>\n\
	</html>\n";
	return (footer);
}

std::string Autoindex::getFileLink(const unsigned char fileType, std::string fileName)
{
	std::string fileLink;

	fileLink = "<a href=\"" + path + "/" + fileName;
	if (fileType == DT_DIR)
		fileLink += "/";
	if (fileType == DT_DIR)
		fileLink += "\"> ";
	else
		fileLink += "\"> ";
	fileLink += fileName + "</a>";
	set_data(&fileLink);
	return (fileLink);
}

std::string Autoindex::create_file_link(const unsigned char fileType, const std::string &fileName)
{
	struct stat fileInfos;
	std::string link;
	std::string filePath(path_d + fileName);
	if (fileName == "." || fileName == "..")
    {
		return ("");
    }
	link = "\t\t\t<tr>\n";
	link += getFileLink(fileType, fileName);
	link += "\t\t\t</tr>\n";
	return (link);
}

void Autoindex::generateIndexPage()
{
	DIR *directory;
	struct dirent *file;

	directory = opendir(path_d.c_str());
	if (!directory)
	{
		checker = true;
		return ;
	}
	index += create_header();
	for (file = readdir(directory); file != NULL; file = readdir(directory))
	{
		index += create_file_link(file->d_type, std::string(file->d_name));
	}
	index += footer();
	closedir(directory);
}

void Autoindex::set_data(std::string *data)
{
	*data = "\t\t\t\t<td class=\"border\">" + *data + "</td>\n";
}

std::string Autoindex::getDirectoryPath() const
{
	return (path_d);
}

std::string Autoindex::getIndexPage() const
{
	return (index);
}

bool Autoindex::get_checker()
{
	return (checker);
}