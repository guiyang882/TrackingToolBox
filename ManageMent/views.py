from django.shortcuts import render
from django.http import HttpResponseRedirect
from django.contrib.auth.models import User
from django.core.urlresolvers import reverse
from django.contrib import auth

from django.contrib.auth.decorators import login_required
from django.contrib.auth.decorators import user_passes_test

from django.core.paginator import Paginator
from django.core.paginator import EmptyPage
from django.core.paginator import PageNotAnInteger

from ManageMent.utils import permission_check
from ManageMent.models import MyUser
from ManageMent.models import Video
from ManageMent.models import Photo

# Create your views here.

def index(request):
    user = request.user if request.user.is_authenticated() else None
    content = {
        "active_menu" : "homepage",
        "user" : user,
    }
    return render(request, "management/index.html", content)

def signup(request):
    if request.user.is_authenticated():
        return HttpResponseRedirect(reverse('homepage'))
    state = None
    if request.method == 'POST':
        password = request.POST.get('password', '')
        repeat_password = request.POST.get('repeat_password', '')
        if password == '' or repeat_password == '':
            state = 'empty'
        elif password != repeat_password:
            state = 'repeat_error'
        else:
            username = request.POST.get('username', '')
            if User.objects.filter(username=username):
                state = 'user_exist'
            else:
                new_user = User.objects.create_user(username=username, password=password,
                                                    email=request.POST.get('email', ''))
                new_user.save()
                new_my_user = MyUser(user=new_user, nickname=request.POST.get('nickname', ''))
                new_my_user.save()
                state = 'success'
    content = {
        'active_menu': 'homepage',
        'state': state,
        'user': None,
    }
    return render(request, 'management/signup.html', content)

def login(request):
    if request.user.is_authenticated():
        return HttpResponseRedirect(reverse('homepage'))
    state = None
    if request.method == 'POST':
        username = request.POST.get('username', '')
        password = request.POST.get('password', '')
        user = auth.authenticate(username=username, password=password)
        if user is not None:
            auth.login(request, user)
            return HttpResponseRedirect(reverse('homepage'))
        else:
            state = 'not_exist_or_password_error'
    content = {
        'active_menu': 'homepage',
        'state': state,
        'user': None
    }
    return render(request, 'management/login.html', content)

def logout(request):
    auth.logout(request)
    return HttpResponseRedirect(reverse('homepage'))

@login_required
def set_password(request):
    user = request.user
    state = None
    if request.method == 'POST':
        old_password = request.POST.get('old_password', '')
        new_password = request.POST.get('new_password', '')
        repeat_password = request.POST.get('repeat_password', '')
        if user.check_password(old_password):
            if not new_password:
                state = 'empty'
            elif new_password != repeat_password:
                state = 'repeat_error'
            else:
                user.set_password(new_password)
                user.save()
                state = 'success'
        else:
            state = 'password_error'
    content = {
        'user': user,
        'active_menu': 'homepage',
        'state': state,
    }
    return render(request, 'management/set_password.html', content)

@user_passes_test(permission_check)
def upload_videos(request):
    user = request.user
    state = None
    if request.method == 'POST':
        new_video = Video(
            caption=request.POST.get('name', ''),
            author=user,
            content=request.FILES.get('video', ''),
            category="default",
            description="default"
        )
        new_video.save()
        state = 'success'
    content = {
        'user': user,
        'active_menu': 'upload_videos',
        'state': state,
    }
    return render(request, 'management/upload_videos.html', content)

@user_passes_test(permission_check)
def upload_images(request):
    user = request.user
    state = None
    if request.method == 'POST':
        new_img = Photo(
            caption=request.POST.get('name', ''),
            author=user,
            image=request.FILES.get('img', ''),
            category="default",
            description=request.POST.get('description', '')
        )
        new_img.save()
        state = 'success'
    content = {
        'user': user,
        'state': state,
        'active_menu': 'upload_images',
    }
    return render(request, 'management/upload_images.html', content)

def view_images_list(request):
    user = request.user if request.user.is_authenticated() else None
    category_list = Photo.objects.values_list('category', flat=True).distinct()
    query_category = request.GET.get('category', 'all')
    if (not query_category) or Photo.objects.filter(category=query_category).count() is 0:
        query_category = 'all'
        photo_list = Photo.objects.all()
    else:
        photo_list = Photo.objects.filter(category=query_category)

    if request.method == 'POST':
        keyword = request.POST.get('keyword', '')
        photo_list = Photo.objects.filter(name__contains=keyword)
        query_category = 'all'

    paginator = Paginator(photo_list, 5)
    page = request.GET.get('page')
    try:
        book_list = paginator.page(page)
    except PageNotAnInteger:
        book_list = paginator.page(1)
    except EmptyPage:
        book_list = paginator.page(paginator.num_pages)
    content = {
        'user': user,
        'active_menu': 'view_images',
        'category_list': category_list,
        'query_category': query_category,
        'photos_list': photo_list,
    }
    return render(request, 'management/view_images_list.html', content)

def image_detail(request):
    user = request.user if request.user.is_authenticated() else None
    image_id = request.GET.get('id', '')
    if image_id == '':
        return HttpResponseRedirect(reverse('view_images'))
    try:
        image = Photo.objects.get(pk=image_id)
    except Photo.DoesNotExist:
        return HttpResponseRedirect(reverse('view_images'))
    content = {
        'user': user,
        'active_menu': 'view_images',
        'image': image
    }
    print content["image"]
    return render(request, 'management/image_detail.html', content)

def view_videos_list(request):
    user = request.user if request.user.is_authenticated() else None
    category_list = Video.objects.values_list('category', flat=True).distinct()
    query_category = request.GET.get('category', 'all')
    if (not query_category) or Video.objects.filter(category=query_category).count() is 0:
        query_category = 'all'
        video_list = Video.objects.all()
    else:
        video_list = Video.objects.filter(category=query_category)

    if request.method == 'POST':
        keyword = request.POST.get('keyword', '')
        video_list = Video.objects.filter(name__contains=keyword)
        query_category = 'all'

    paginator = Paginator(video_list, 5)
    page = request.GET.get('page')
    try:
        book_list = paginator.page(page)
    except PageNotAnInteger:
        book_list = paginator.page(1)
    except EmptyPage:
        book_list = paginator.page(paginator.num_pages)
    content = {
        'user': user,
        'active_menu': 'view_videos',
        'category_list': category_list,
        'query_category': query_category,
        'videos_list': video_list,
    }
    return render(request, 'management/view_videos_list.html', content)