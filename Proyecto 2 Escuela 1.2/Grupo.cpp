#include "Grupo.h"

Grupo::Grupo(std::string NCR, int cupo, Horario* horario)
{
	this->NCR = NCR;
	this->cupo = cupo;
	this->cantidadEstudiantes = 0;
	this->horario = horario;
	this->profesor = nullptr;
	estudiantes = new ListaEstudiante();
}

Grupo::~Grupo()
{ 
	//La relacion es agregacion por lo que los estudiantes no se eliminan
	//solamente vaciamos la lista
	if (estudiantes != nullptr) {
		NodoEstudiante* aux = estudiantes->getPrimer();
		while (aux != NULL)
		{
			if (aux->getEstudiante() != nullptr) {
				aux->setEstudiante(nullptr);
			}
			aux = aux->getSiguiente();
		}
	}
	delete estudiantes;
	delete horario;
}

std::string Grupo::getNCR()
{
	return NCR;
}

int Grupo::getCupo()
{
	return cupo;
}

int Grupo::getCantidadEstudiantes()
{
	return cantidadEstudiantes;
}

bool Grupo::ExisteEstudiante(std::string cedula)
{
	return estudiantes->repetido(cedula);
}

Estudiante* Grupo::buscarEstudiante(std::string cedula)
{
	return estudiantes->buscarEstudiante(cedula);
}

Horario* Grupo::getHorario()
{
	return horario;
}

Profesor* Grupo::getProfesor()
{
	return profesor;
}

void Grupo::setCupo(int cupo)
{
	this->cupo = cupo;
}

void Grupo::setCantidadEstudiantes(int cantidadEstudiantes)
{
	this->cantidadEstudiantes = cantidadEstudiantes;
}

bool Grupo::setProfesor(Profesor* profesor)
{
	if (this->profesor == nullptr)
	{
		this->profesor = profesor;
		return true;
	}
	else
	{
		return false;
	}
}

bool Grupo::matricularEstudiante(Estudiante* estudiante)
{
	if (cantidadEstudiantes < cupo)
	{
		if (estudiantes->insertarEstudiante(estudiante))
		{
			cantidadEstudiantes++;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Grupo::darBajaEstudiante(Estudiante* estudiante)
{
	if (cantidadEstudiantes > 0)
	{
		estudiantes->eliminarEstudiante(estudiante->getcedula());
		cantidadEstudiantes--;
		return true;
	}
	else
	{
		return false;
	}
}

std::string Grupo::toString()
{
	std::stringstream s;
	s << "NCR: " << NCR << "\n";
	if (profesor != nullptr)
	{
		s << "Profesor: " << profesor->getnombre() << "\n";
	}
	else
	{
		s << "Profesor: No asignado" << "\n";
	}
	s << "cupo: " << cupo << "\n";
	s << "cantidadEstudiantes: " << cantidadEstudiantes << "\n";
	s << "horario: " << horario->toString() << "\n";
	s << "Estudiantes: " << estudiantes->toString() << "\n";
	
	return s.str();
	
}

std::string Grupo::toStringEstudiantes()
{
	return estudiantes->toString();
}

std::string Grupo::toStringCSV()
{
	std::stringstream s;
	std::string ced;
	if (profesor != nullptr)
	{
		ced = profesor->getcedula();
	}
	else
	{
		ced = "NULL";
	}

	s << NCR << "," << cupo << "," << cantidadEstudiantes << "," << horario->toStringCSV() << "," << ced<<",";
	return s.str();
	
}

std::string Grupo::toStringIDCSV()
{

	return estudiantes->toStringIDCSV();

}



