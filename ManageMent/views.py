from django.shortcuts import render

# Create your views here.

def index(request):
    user = request.user if request.user.is_authenticated() else None
    content = {
        "active_menu" : "homepage",
        "user" : user,
    }
    return render(request, "management/index.html", content)