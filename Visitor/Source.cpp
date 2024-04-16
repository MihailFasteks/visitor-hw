#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Processor;
class Hdd;
class RAM;
class VideoCard;

class IVisitor abstract
{
public:
	virtual void VisitProcessor(Processor* proc) abstract;
	virtual void VisitHdd(Hdd* hdd) abstract;
	virtual void VisitRAM(RAM* ram) abstract;
	virtual void VisitVideoCard(VideoCard* vc) abstract;
};

class AbstractDevice abstract
{
	string Producer;
public:
	virtual void Accept(IVisitor* visitor)abstract;
	string GetProducer()
	{ 
		return Producer;
	}
	void SetProducer(string Producer)
	{
		this->Producer = Producer;
	}
};

class Processor: public AbstractDevice
{
	string Frequency;
	string CoreCount;
public:
	string GetFrequency()
	{
		return  Frequency;
	}
	void SetFrequency(string Frequency)
	{
		this->Frequency = Frequency;
	}
	string GetCoreCount()
	{
		return CoreCount;
	}
	void SetCoreCount(string CoreCount)
	{
		this->CoreCount = CoreCount;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitProcessor(this);
	}
};

class Hdd: public AbstractDevice
{
	string Volume;
	string Type;
public:
	string GetVolume()
	{
		return Volume;
	}
	void SetVolume(string Volume)
	{
		this->Volume = Volume;
	}
	string GetType()
	{
		return Type;
	}
	void SetType(string Type)
	{
		this->Type = Type;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitHdd(this);
	}
};
class RAM : public AbstractDevice
{
	string Frequency;
	string V;
public:
	string GetFrequency()
	{
		return  Frequency;
	}
	void SetFrequency(string Frequency)
	{
		this->Frequency = Frequency;
	}
	string GetV()
	{
		return V;
	}
	void SetV(string v)
	{
		this->V = v;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitRAM(this);
	}
};
class VideoCard : public AbstractDevice
{
	string Frequency;
	string V;
	string Model;
	string Type;
public:
	string GetFrequency()
	{
		return  Frequency;
	}
	void SetFrequency(string Frequency)
	{
		this->Frequency = Frequency;
	}
	string GetV()
	{
		return V;
	}
	void SetV(string v)
	{
		this->V = v;
	}
	void SetModel(string model) {
		this->Model = model;
	}
	string GetModel() {
		return Model;
	}
	void SetType(string type) {
		this->Type = type;
	}
	string GetType() {
		return Type;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitVideoCard(this);
	}
};

// сериализатор в HTML
class HtmlVisitor : public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		ofstream out("Processor.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + proc->GetProducer() + "</td></tr>";
		result += "<tr><td>Frequency<td><td>" + proc->GetFrequency() + "</td></tr>";
		result += "<tr><td>CoreCount<td><td>" + proc->GetCoreCount() + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitHdd(Hdd* hdd) override
	{
		ofstream out("Hdd.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + hdd->GetProducer() + "</td></tr>";
		result += "<tr><td>Type<td><td>" + hdd->GetType() + "</td></tr>";
		result += "<tr><td>Volume<td><td>" + hdd->GetVolume() + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitRAM(RAM* ram) override
	{
		ofstream out("RAM.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>V<td><td>" + ram->GetV() + "</td></tr>";
		result += "<tr><td>Frequency<td><td>" + ram->GetFrequency() + "</td></tr>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitVideoCard(VideoCard* vc) override
	{
		ofstream out("VideoCard.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Frequency<td><td>" + vc->GetFrequency() + "</td></tr>";
		result += "<tr><td>Type<td><td>" + vc->GetType() + "</td></tr>";
		result += "<tr><td>V<td><td>" + vc->GetV() + "</td></tr>";
		result += "<tr><td>Model<td><td>" + vc->GetModel() + "</td></tr>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
};

// сериализатор в XML
class XmlVisitor: public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		ofstream out("Processor.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<Processor><Producer>" + proc->GetProducer() + "</Producer>" +
			"<Frequency>" + proc->GetFrequency() + "</Frequency>" +
			"<CoreCount>" + proc->GetCoreCount() + "</CoreCount></Processor>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitHdd(Hdd* hdd) override
	{
		ofstream out("Hdd.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<HDD><Producer>" + hdd->GetProducer() + "</Producer>" +
			"<Type>" + hdd->GetType() + "</Type>" +
			"<Volume>" + hdd->GetVolume() + "</Volume></HDD>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitRAM(RAM* ram) override
	{
		ofstream out("RAM.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<RAM><V>" + ram->GetV() + "</V>" +
			"<Frequency>" + ram->GetFrequency() + "</Frequency></RAM>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitVideoCard(VideoCard* vc) override
	{
		ofstream out("VideoCard.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<VideoCard><V>" + vc->GetV() + "</V>" +
			"<Frequency>" + vc->GetFrequency() + "</Frequency>" +
			"<Type>" + vc->GetType() + "</Type>" +
			"<Model>" + vc->GetModel() + "</Model></VideoCard>";
		out.write(result.c_str(), result.size());
		out.close();
	}
};
class TextVisitor : public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		ofstream out("Processor.txt");
		out << "Processor Information:" << endl;
		out << "Producer: " << proc->GetProducer() << endl;
		out << "Frequency: " << proc->GetFrequency() << endl;
		out << "Core Count: " << proc->GetCoreCount() << endl;
		out.close();
	}

	void VisitHdd(Hdd* hdd) override
	{
		ofstream out("Hdd.txt");
		out << "HDD Information:" << endl;
		out << "Producer: " << hdd->GetProducer() << endl;
		out << "Type: " << hdd->GetType() << endl;
		out << "Volume: " << hdd->GetVolume() << endl;
		out.close();
	}

	void VisitRAM(RAM* ram) override
	{
		ofstream out("RAM.txt");
		out << "RAM Information:" << endl;
		out << "V: " << ram->GetV() << endl;
		out << "Frequency: " << ram->GetFrequency() << endl;
		out.close();
	}

	void VisitVideoCard(VideoCard* vc) override
	{
		ofstream out("VideoCard.txt");
		out << "Video Card Information:" << endl;
		out << "Frequency: " << vc->GetFrequency() << endl;
		out << "Type: " << vc->GetType() << endl;
		out << "V: " << vc->GetV() << endl;
		out << "Model: " << vc->GetModel() << endl;
		out.close();
	}
};
class ConsoleVisitor : public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		
		cout << "Processor Information:" << endl;
		cout << "Producer: " << proc->GetProducer() << endl;
		cout << "Frequency: " << proc->GetFrequency() << endl;
		cout << "Core Count: " << proc->GetCoreCount() << endl;
		
	}

	void VisitHdd(Hdd* hdd) override
	{
		
		cout << "HDD Information:" << endl;
		cout << "Producer: " << hdd->GetProducer() << endl;
		cout << "Type: " << hdd->GetType() << endl;
		cout << "Volume: " << hdd->GetVolume() << endl;
		
	}

	void VisitRAM(RAM* ram) override
	{
		
		cout << "RAM Information:" << endl;
		cout << "V: " << ram->GetV() << endl;
		cout << "Frequency: " << ram->GetFrequency() << endl;
		
	}

	void VisitVideoCard(VideoCard* vc) override
	{
		
		cout << "Video Card Information:" << endl;
		cout << "Frequency: " << vc->GetFrequency() << endl;
		cout << "Type: " << vc->GetType() << endl;
		cout << "V: " << vc->GetV() << endl;
		cout << "Model: " << vc->GetModel() << endl;
		
	}
};

class PC
{
	vector<AbstractDevice*> devices;
public:
	void Add(AbstractDevice* d)
	{
		devices.push_back(d);
	}
	void Remove(AbstractDevice* d)
	{
		auto iter = find(devices.begin(), devices.end(), d);
		if(iter != devices.end())
			devices.erase(iter);
	}
	void Accept(IVisitor* visitor)
	{
		for(AbstractDevice* d : devices)
			d->Accept(visitor);
	}
};

int main()
{
	PC* pc = new PC();
	Processor *p = new Processor;
	p->SetProducer("Intel");
	p->SetFrequency("3.5");
	p->SetCoreCount("4");
	pc->Add(p);
	Hdd *hdd = new Hdd;
	hdd->SetProducer("Western Digital");
	hdd->SetType("SATA III");
	hdd->SetVolume("2");
	pc->Add(hdd);
	RAM* ram = new RAM;
	ram->SetFrequency("4.0");
	ram->SetV("16GB");
	pc->Add(ram);
	VideoCard* vc = new VideoCard;
	vc->SetFrequency("3.8");
	vc->SetModel("STR-09-08-76");
	vc->SetType("ST-over9");
	vc->SetV("128 MB");
	pc->Add(vc);
	HtmlVisitor *html = new HtmlVisitor;
	pc->Accept(html);
	XmlVisitor *xml = new XmlVisitor;
	pc->Accept(xml);
	TextVisitor* text = new TextVisitor;
	pc->Accept(text);
	ConsoleVisitor* console = new ConsoleVisitor;
	pc->Accept(console);
	delete html;
	delete xml;
	delete text;
	delete console;
	delete hdd;
	delete p;
	delete ram;
	delete vc;
	delete pc;

	system("pause");
}
